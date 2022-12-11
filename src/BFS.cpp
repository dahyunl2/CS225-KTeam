/*create traversal to find the shortest routes between the airports with a given departing location 
and arriving location based on the least amount of connecting flights*/

#include "BFS.h"
#include <climits>

//Implement constructor which can call a graph constructor
BFS::BFS(const string &airportFile, const string &routeFile){
    string rfile = routeFile;
    string afile = airportFile;
    airport_graph = Graph(afile, rfile);
}

////returns a vector of traversed airports in BFS order
vector<string> BFS::BFS_All(int source){
    vector<string> result; //string vector that covers all of the airports
    vector<bool> visit(14111, false); //initialize all airports to not visited

    //initialization
    queue<int> queue;
    queue.push(source);
    int current = source;
    visit[current] = true;
    
    //queue
    while (!queue.empty()) {
        current = queue.front();
        result.push_back(airport_graph.getAirportName(current));
        
        //confirm the ID of the adjacent airport is unvisited
        //check enqueue neighbor airport and set as visited
        for (auto it : airport_graph.getAdjAP(current)){
            if (visit[it.first] != true) { 
                queue.push(it.first);  
                visit[it.first] = true;
            }
        }
        queue.pop();
    }
    return result;
}

//returns a vector of strings of the traversed airports in BFS order
vector<string> BFS::BFS_move(int source, int moves){
    //make vector covering all the airports and initialize all airports to not visited as false
    vector<string> result;
    vector<bool> visit(14111, false);
    
    //initialization
    queue<int> queue;
    queue.push(source);
    int current = source;
    visit[current] = true;

    //queue
    while (!queue.empty()) {
        if(result.size() == (unsigned)moves + 1)
            return result;
        current = queue.front();
        result.push_back(airport_graph.getAirportName(current));
        //iterate thorugh all adjacent airports of the current 
        //check if the adjacent airport ID is unvisited
        //check enqueue neighbor airport and set as visited
        for (auto it : airport_graph.getAdjAP(current)){
            if (visit[it.first] != true) { 
                queue.push(it.first);  
                visit[it.first] = true;
            }
        }
        queue.pop();
    }

    return result;
}

//returns a string vector of the traversed airports in BFS order
//if there is no traversal between the two airports, it returns an empty vector
vector<string> BFS::BFS_goal(int dest, int source){
    //make vector covering all the airports and initialize all airports to not visited as false
    vector<string> result = vector<string>();
    vector<bool> visit(14111, false);
    
    queue<int> queue;
    queue.push(source);
    int current = source;
    visit[current] = true;
    
    //queue
    while (!queue.empty()) {
        current = queue.front();
        if(current == dest){
            result.push_back(airport_graph.getAirportName(current));
            break;
        }
        result.push_back(airport_graph.getAirportName(current));
        for (auto it : airport_graph.getAdjAP(current)){
            if (visited[it.first] != true) { 
                queue.push(it.first);  
                visit[it.first] = true;
            }
        }
        queue.pop();
    }
    //If destination is not reached, empty vector is returned
    if(current != dest) {
        cout << "There is no path from " << airport_graph.getAirportName(dest) << "to " << airport_graph.getAirportName(source) << endl;
        return vector<string> ();
    }
    return result;
}
