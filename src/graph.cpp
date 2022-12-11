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
void Graph::loadVertex(int id, Airport airport)
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
                loadVertex(airport.getAPID(), airport);
            }
        }
        file.close(); 
    }
}

unordered_map<int, Airport> Graph::getVertices(){
    return airportMap;
}

//
string Graph::getAirportName(int ID){
    auto it = airportMap.find(ID);
    if(it != airportMap.end()){
        return airportMap[ID].getAPName();
    }
    return string();
}

std::vector<std::string> Graph::_lineToFlightContents(string & line){

    auto vect = splice_(line);
    if (vect.size() != 8)
        return std::vector<std::string>();


    return vect;
}


std::vector<std::string> Graph::splice_ (string & line) {
    std::string currString = "";
    std::vector<std::string> vect;
    int cnt = 0;

    for (size_t i = 0; i < line.size(); ++i) {
        char current = line[i];
        if(current == '\\') {
            return vect;
        }
        if (current == ',') {
            cnt++;
        }
    }

    if(cnt != 8) {
        return vect;
    }
           
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


void Graph::loadEdge(Flight flight){       
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
                    loadEdge(f);
            }
        }
        file.close(); 
    }
}

unordered_map<int, Flight> Graph::getAdjAP(int AirportID) {
    auto it = airportMap.find(AirportID);
    if(it != airportMap.end()){
        Airport& AP = airportMap[AirportID];
        return AP.destAPs;
    }
    return unordered_map<int, Flight> ();
}

// Calculate Weight for Flight
double Graph::calcWeight(int depID, int destID){
    double lat1 = degreeToRadian(airportMap[depID].getAPLat());
    double lon1 = degreeToRadian(airportMap[depID].getAPLat());
    double lat2 = degreeToRadian(airportMap[destID].getAPLat());
    double lon2 = degreeToRadian(airportMap[destID].getAPLat());

    double lan_diff = lon2 - lon1;
    double lat_diff = lat2 - lat1;
    
    long double to_return = pow(sin(lat_diff / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(lan_diff / 2), 2);
    to_return = 2 * asin(sqrt(to_return));
    double R = 6371;
    to_return *= R;
    return to_return; 
}


//helper function to calcWeight ( M_PI is the constant of pi accurate to 1e-30
double Graph::degreeToRadian(double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

//traversal graph to populate adj matrix for pagerank
void Graph::adjMatrix(PageRank *pr_obj){

    //determine and set the dimention
    int size = airportMap.size();
    pr_obj->adj.resize(size,vector<double>(size));
    pr_obj->name_list.resize(size);
    pr_obj->num = size;


    //initialize obj matrix
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            pr_obj->adj[i][j] = 0.0;
        }        
    }

    //populate the namelist of pagerank obj
    int x = 0;
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        if(it->second.getAPID() == 0){
            continue;
        }
        pr_obj->name_list[x] = (it->second.getAPID());
        x++;     
    }
    

    /*check every flight of every airport
    put the weight into the adj matrix according to the order of the namelist*/
    x = 0;
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        if(x == size) break;
        if(it->second.getAPID() == 0){
            continue;
        }

        /*
        check the flights of the current vertices/airport
            & find out the proper place for the weight of the current flight according to the namelist
        */
        for(auto flight = it->second.destAPs.begin(); flight != it->second.destAPs.end(); ++flight){
            int y = 0;
            for (auto temp = pr_obj->name_list.begin(); temp != pr_obj->name_list.end(); ++temp) {
                if (*temp == flight->second.gettoWhereId()) break;
                y++;
            } 
            if(y == size) break;
            pr_obj->adj[y][x] = flight->second.getDistance();
        }
        x++;
    }
}
