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


Graph::Graph(){

}


Graph::Graph(std::string & airportData, std::string & routesData){
    loadVertices(airportData);
    loadEdges(routesData);
}

void Graph::insertVertex(int id, Airport airport)
{
    airportMap[id] = airport;
}


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
    return Flight();
}


void Graph::insertEdge(Flight flight){       
    int source = flight.getfromWhereId();
    int dest = flight.gettoWhereId();

    if (airportMap[source].destAPs.find(dest) == airportMap[source].destAPs.end())   
        (airportMap[source].destAPs)[dest] = flight;
}
 
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
                    insertEdge(f);
            }
        }
        file.close(); 
    }
}