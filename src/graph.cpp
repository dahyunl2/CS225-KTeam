//Graphs Class

#include "graph.h"
#include <math.h> 
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;


//default constructor
Graph::Graph(){

}


//constructor with loading airport.dat and routes.dat
//creates vertices and edges
Graph::Graph(std::string & airportData, std::string & routesData){
    loadVertices(airportData);
    loadEdges(routesData);
}

//construct the vertices
//such that each airport object is connected with its ID
void Graph::insertVertex(int id, Airport airport)
{
    //vertices
    airportMap[id] = airport;
    //hihi
}


//takes airport.dat and insert each airport into the class line by line
void Graph::loadVertices(std::string & fileName)
{
    std::fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currentL;
        while(getline(file, currentL)){
            int cnt = 0;
            for(unsigned i = 0; i < currentL.size(); ++i){
                char here = currentL[i];
                if(here == ',')
                    cnt++;
            }
            if(cnt == 13){
                Airport airport(currentL);
                insertVertex(airport.getAPID(), airport);
            }
        }
        file.close(); 
    }
}

string Graph::getAirportName(int ID){
    auto it = airportMap.find(ID);
    if(it != airportMap.end()){
        return airportMap[ID].getAPName();
    }
    return string();
}

std::vector<std::string> Graph::_lineToFlightContents(string & line){

    auto vect = splice_(line);
    if (vect.size() != 9)
        return std::vector<std::string>();


    return vect;
}


std::vector<std::string> Graph::splice_ (string & line) {
    std::string currString = "";
    std::vector<std::string> vect;

     for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];
        if(current == ',') {
            vect.push_back(currString);
            currString = "";
        }
        else
            currString += current;
    }

    return vect;
}


Flight Graph::createEdge(std::vector<std::string> flightVector){
    int source = stoi(flightVector[3], nullptr);
    int dest = stoi(flightVector[5], nullptr);
    auto it = airportMap.find(source);
    auto it2 = airportMap.find(dest);
    if(it != airportMap.end() && it2 != airportMap.end()){
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    //if either airport is not inserted, return default constructed flight
    return Flight();
}


void Graph::insertEdge(Flight flight){       
    int source = flight.getfromWhereId();
    int dest = flight.gettoWhereId();

    if (airportMap[source].destAPs.find(dest) == airportMap[source].destAPs.end())   
        (airportMap[source].destAPs)[dest] = flight;
}


//similar to insert all vertices
//iterates through routes.dat and insert flight for each line 
void Graph::loadEdges(std::string & fileName){
    std::fstream file;
    //open the file
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;
                    
        //iterate through each line of the file
        while(getline(file, currLine)){ 
            std::vector<std::string> currVect = _lineToFlightContents(currLine);
            
            if(currVect != std::vector<std::string>()){
                Flight f = createEdge(currVect);
                Flight defaultF = Flight();
                if(!(f == defaultF))
                    insertEdge(f);
            }
        }
        file.close(); 
    }
}

// Calculate Weight for Flight
double Graph::calcWeight(int fromID, int toID){
    double lat1 = radianConvert(vertices[fromID].getAirportLatitude());
    double lon1 = radianConvert(vertices[fromID].getAirportLongitude());
    double lat2 = radianConvert(vertices[toID].getAirportLatitude());
    double lon2 = radianConvert(vertices[toID].getAirportLongitude());

    double lonDiff = lon2 - lon1;
    double latDiff = lat2 - lat1;
    
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    double R = 6371;
    ans *= R;
    return ans; 
}


//helper function to calcWeight ( M_PI is the constant of pi accurate to 1e-30
double Graph::radianConvert(double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
