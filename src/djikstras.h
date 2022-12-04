#pragma once
#include "graph.h"
#include "Flight.h"
#include "airport.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Djikstras {
    public:
        //constructor
        Djikstras (Graph graph, string AirportFrom, string AirportTo);

        //getter
        vector<string> getVertices() const;
        double getMinDist() const;
        vector<pair<int, double>> getNeighbor(string root);

        //checks whether the vertex of the node exists 
        bool hasVertex(string node);

        //helpers
        void mapsInitialize(vector<string>& v, unordered_map<int, Airport> Map, string AirportFrom,string AirportTo);
        void findPaths(unordered_map<int, Airport> Map,string AirportFrom,string AirportTo);
    private:
        double path;
        map<string, double> distances;
        vector<string> vertices;
        unordered_map <string, bool> isVisited;
        unordered_map<string, string> prevNodes;
        
        priority_queue<pair<double, string>, vector<pair<double, string>>,greater<pair<double, string>> > myQueue;
        unordered_map<string, unordered_map<int, Flight> > neighbor_list;
};