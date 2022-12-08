/*create traversal to find the shortest routes between the airports with a given departing location 
and arriving location based on the least amount of connecting flights*/

#include "BFS.h"
#include <climits>


BFS::BFS(const string &airportFile, const string &routeFile){
    string afile = airportFile;
    string rfile = routeFile;
    airport_graph = Graph(afile, rfile);
}

vector<string> BFS::BFS_All(int source){
    vector<string> result;
    vector<bool> visited(14111, false);

    queue<int> queue;
    queue.push(source);
    int current = source;
    visited[current] = true;
    

    while (!queue.empty()) {
        current = queue.front();
        result.push_back(airport_graph.getAirportName(current));
        
        for (auto it : airport_graph.getAdjAP(current)){
            if (visited[it.first] != true) { 
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    return result;
}


vector<string> BFS::BFS_move(int sourceAP, int moves){
    vector<string> result;
    vector<bool> visited(14111, false);
    
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;

    while (!queue.empty()) {
        if(result.size() == (unsigned)moves + 1)
            return result;
        currentAP = queue.front();
        result.push_back(airport_graph.getAirportName(currentAP));
        for (auto it : airport_graph.getAdjAP(currentAP)){
            if (visited[it.first] == false) { 
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }

    return result;
}


vector<string> BFS::BFS_goal(int dest, int source){
    vector<string> result = vector<string>();
    vector<bool> visited(14111, false);
    
    queue<int> queue;
    queue.push(source);
    int current = source;
    visited[current] = true;
    
    while (!queue.empty()) {
        current = queue.front();
        if(current == dest){
            result.push_back(airport_graph.getAirportName(current));
            break;
        }
        result.push_back(airport_graph.getAirportName(current));
        for (auto it : airport_graph.adjVertWithWeight(current)){
            if (visited[it.first] != true) { 
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    if(current != dest) {
        cout << "There is no path from " << airport_graph.getAirportName(dest) << "to " << airport_graph.getAirportName(source) << endl;
        return vector<string> ();
    }
    return result;
}
