#include "Djikstras.h"
#include <map>
#include <climits>
#include <stack>

using namespace std;

//Constructor which operate the process of finding the shortest path between airports 
//and store that path to the member variable path -> getMinDist will return this path
//input: graph;graph of connected airports, AirportFrom;starting point, AirportTo;destination
//return: N/A 
//helpers: mapsInitialize, findpaths
Djikstras::Djikstras(Graph graph, string AirportFrom, string AirportTo) {
    vertices.clear();
    vector<string> v;  

    unordered_map<int, Airport> Map = graph.getVertices();
    mapsInitialize(v, Map, AirportFrom, AirportTo);
    
    pair<double,string> start = make_pair(0.0, AirportFrom);
    myQueue.push(start);

    for(auto it = Map.begin(); it != Map.end(); ++it) {
        pair<string, unordered_map<int, Flight>> p=make_pair(it->second.getAPName(), it->second.destAPs);
        neighbor_list.insert(p);
    }

    findPaths(Map,AirportFrom, AirportTo);

    //min dist
    path = distances[AirportTo];

    string key = AirportTo;
    vertices.push_back(AirportTo);
    while(key != AirportFrom) {
        vertices.push_back(prevNodes[key]);
        key = prevNodes[key];
    }
    std::reverse(vertices.begin(), vertices.end());
}

//helper for constructor
//initializing three maps: distances, isvisited, prevNodes
//input: v; vector made in constructor, Map; map made in constructor, AirportFrom;starting point, AirportTo;destination
//return: N/A 
void Djikstras::mapsInitialize(vector<string>& v, unordered_map<int, Airport> Map,string AirportFrom,string AirportTo){
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
}

//helper for constructor
//finding paths between airports and update the distances with shortest path
//input: Map; map made in constructor, AirportFrom;starting point, AirportTo;destination
//return: N/A 
void Djikstras::findPaths(unordered_map<int, Airport> Map,string AirportFrom,string AirportTo){
    while(AirportTo != myQueue.top().second) {
        pair<double, string> currNode = myQueue.top();
        myQueue.pop();

        vector<pair<string, double>> neighborNames;
        vector<pair<int , double>> neighbors = getNeighbor(currNode.second);
        
        //set neighborNames using neighbors
        for (size_t i=0;i<neighbors.size();i++) {
            auto temp=neighbors[i];
            for (auto j = Map.begin(); j != Map.end(); ++j) {
                if (temp.first == j->first) {
                    pair<string, double> temp2=make_pair(j->second.getAPName(), temp.second);
                    neighborNames.push_back(temp2);
                }
            }
        }

        //change distances using myQueue
        for (size_t i=0;i<neighborNames.size();i++) {
            auto temp=neighborNames[i];
            if (isVisited[currNode.second] == false && isVisited[temp.first] == false) {
                double dist = temp.second;
                if(dist + distances[currNode.second] < distances[temp.first]) {
                    prevNodes[temp.first] = currNode.second;
                    distances[temp.first] = dist + distances[currNode.second];
                    myQueue.push(make_pair(distances[temp.first], temp.first)); 
                }
            }
        }
        isVisited[currNode.second] = true;
    }
}

//finding all of the neighbors (adjacent) airpots of root airport
//input: root; the name of a airport that we want to know the neighbors
//return: vector of pairs<neighboring airport, the distance from this airport to the root>
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

//getter
//return: path; the distance between two airports
double Djikstras::getMinDist() const{
    return path;
}

//getter
//return: vertices; the vector includes all airports in the path
vector<string> Djikstras::getVertices() const{
    return vertices;
}

//check if the airport(node) is included in the neighbor_list
//input: node; the name of the airport that we want to know if it is in the neighbor_list
//return: boolean which indicates if the neighbor_list has node or not
bool Djikstras::hasVertex(string node){
    if (neighbor_list.find(node) != neighbor_list.end()) {
        return true;
    }
    return false;
}