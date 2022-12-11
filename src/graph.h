#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "airport.h"
#include "Flight.h"
#include "PageRank.h"

using namespace std;

class Graph {
    public:
        //default constructor
        Graph();
        //constructor that accepts the airport and routes.dat files
        Graph(string & airportFile, string & routesFile);
        
        //functions to insert vertices
        void loadVertex(int v, Airport ap);
        void loadVertices(std::string & fileName);
        
        //functions to create insert edges
        vector<string> _lineToFlightContents(string & line);
        Flight createEdge(vector<string> flightVector);     
        void loadEdge(Flight f);
        void loadEdges(std::string & fileName);
        
        //function that returns maps of adjacent airports for a given airport id
        unordered_map<int, Flight> getAdjAP(int airportID);


        //functions that return private maps for debugging
        unordered_map<int, Airport> getVertices();
        std::vector<std::string> splice_ (string & line);
        std::string getAirportName(int id);

        // TODP :: function to harvest adjmatrix from a graph obj
        void adjMatrix(PageRank *pr_obj);
    private:
        //functions that calculate the weight of an edge
        double calcWeight(int depID, int destID);
        double degreeToRadian(double degree);
        
        //each graph object hosts a map of airports to its corresponding ID
        unordered_map<int, Airport> airportMap;
};