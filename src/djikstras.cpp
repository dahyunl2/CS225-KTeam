#include "Djikstras.h"
#include <map>
#include <climits>
#include <stack>

using namespace std;

//constructor which operate the process of finding the shortest path between two airports
//graph: graph of connected airports, AirportFrom: starting point, AirportTo: destination
Djikstras::Djikstras(Graph graph, string AirportFrom, string AirportTo) {
    vertices.clear();
    vector<string> v;  

    unordered_map<int, Airport> Map = graph.getVertices();

    for (auto i = Map.begin(); i != Map.end(); ++i) {
        string name=i->second.getAPName();
        v.push_back(name);
        if(name != AirportFrom) {
            prevNodes.insert(make_pair(name, ""));
            distances.insert(make_pair(name, INT_MAX));
            isVisited.insert(make_pair(name, false));
        }
        else {
            prevNodes.insert(make_pair(name, ""));
            distances.insert(make_pair(name, 0.0));
            isVisited.insert(make_pair(name, false));
        }
    }
    pair<double,string> init = make_pair(0.0, AirportFrom);
    myQueue.push(init);

    //Not yet completed, need to add more
}

vector<pair<int, double>> Djikstras::getNeighbor(string root){
    vector<pair<int,double>> vertex_v;
    auto here = neighbor_list.find(root);
    
    if (here == neighbor_list.end()){
        return vertex_v;
    }
    else {
        unordered_map<int, Flight> &map = neighbor_list.at(root);
        for (auto i = map.begin(); i != map.end(); i++){
            pair <int,double> p (i->first, i->second.getDistance());
            vertex_v.push_back(p);
        }
        return vertex_v;
    }
}

//getter which return the distance between two airports
double Djikstras::getMinDist() const{
    return path;
}

//getter which return the vector includes all airports in the path
vector<string> Djikstras::getVertices() const{
    return vertices;
}

//check if the airport(node) is included in the neighbor_list
bool Djikstras::hasVertex(string node){
    if (neighbor_list.find(node) != neighbor_list.end()) {
        return true;
    }
    return false;
}