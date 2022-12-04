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

//load individual airport to map with key value of airport id
void Graph::loadVertex(int id, Airport airport)
{
    airportMap[id] = airport;
}


//load airport data and insert all airports into a map
void Graph::loadVertices(std::string & fileName)
{
    std::fstream file;
    file.open(fileName, ios::in);
    const int max_count = 13;
    if (file.is_open()){   
        std::string cur_line;
        while(getline(file, cur_line)){
            int count = 0;
            for(unsigned i = 0; i < cur_line.size(); ++i){
                char here = cur_line[i];
                if(here == ',')
                    count++;
            }
            if(count == max_count){
                Airport airport(cur_line);
                loadVertex(airport.getAPID(), airport);
            }
        }
        file.close(); 
    }
}

//getter for airport map
unordered_map<int, Airport> Graph::getVertices(){
    return airportMap;
}

//get airport namee with ID
string Graph::getAirportName(int ID){
    auto iter = airportMap.find(ID);
    if(iter == airportMap.end()){
        return string();    
    }
    return airportMap[ID].getAPName();
}

// helper function for loading edges
std::vector<std::string> Graph::_lineToFlightContents(string & line){

    auto vect = splice_(line);
    if (vect.size() != 9)
        return std::vector<std::string>();

    return vect;
}

// helper function for loading edges
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


// creates flight (edge)
Flight Graph::createEdge(std::vector<std::string> flightVector){
    int source = stoi(flightVector[3], nullptr);
    int dest = stoi(flightVector[5], nullptr);
    auto it = airportMap.find(source);
    auto it2 = airportMap.find(dest);
    if(it != airportMap.end() && it2 != airportMap.end()){
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    
    return Flight();
}


// insert edge to map
void Graph::loadEdge(Flight flight){       
    int source = flight.getfromWhereId();
    int dest = flight.gettoWhereId();

    if (airportMap[source].destAPs.find(dest) == airportMap[source].destAPs.end())   
        (airportMap[source].destAPs)[dest] = flight;
}


// load route file and insert all edges to airport map
void Graph::loadEdges(std::string & fileName){
    std::fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()){   
        std::string currLine;

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

// calculate weight between two airports
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


//helper function for calculating weight
double Graph::degreeToRadian(double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

//populate adj matrix in PageRank class to get the most important airport
void Graph::adjMatrix(PageRank *page_r){

    //determine and set the dimention
    int size = airportMap.size();
    page_r->adj.resize(size,vector<double>(size));
    page_r->name_list.resize(size);
    page_r->num = size;


    //initialize obj matrix
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            page_r->adj[i][j] = 0.0;
        }        
    }

    //populate the namelist of pagerank obj
    int x = 0;
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        if(it->second.getAPID() == 0){
            continue;
        }
        page_r->name_list[x] = (it->second.getAPID());
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
            for (auto temp = page_r->name_list.begin(); temp != page_r->name_list.end(); ++temp) {
                if (*temp == flight->second.gettoWhereId()) break;
                y++;
            } 
            if(y == size) break;
            page_r->adj[y][x] = flight->second.getDistance();
        }
        x++;
    }
}

