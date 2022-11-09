//Graphs Class

#include "airport_graph.h"
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


//helper function that creates an edge from a vector generated from above function
    /*
    before caculating weight, gotta check if source and destination airports are both inserted 
    to avoid inserting an element into the map by using [] operator
        if an edge to the same destination is not found in the list of adjacent airports
        the find function returns the key of the desired element or the end iterator if the element is not found
        only inserts when the flight does not exist in the adjacency list of the airport
    */
Flight Graph::createEdge(std::vector<std::string> flightVector){
    int source = stoi(flightVector[3], nullptr);
    int dest = stoi(flightVector[5], nullptr);
    auto it = vertices.find(source);
    auto it2 = vertices.find(dest);
    if(it != vertices.end() && it2 != vertices.end()){
        double weight = calcWeight(source, dest);
        return Flight(source, dest, weight);
    }
    //if either airport is not inserted, return default constructed flight
    return Flight();
}


void Graph::insertEdge(Flight flight){       
    int source = flight.getSourceId();
    int dest = flight.getDestId();

    if (vertices[source].destAPs.find(dest) == vertices[source].destAPs.end())   
        (vertices[source].destAPs)[dest] = f;
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


 
