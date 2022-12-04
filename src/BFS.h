#pragma once
#include "graph.h"
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

class BFS {
    public:
        BFS(const string &airportFile, const string &routeFile);
        vector<string> BFS_All(int source); /*call the source*/
        vector<string> BFS_move(int sourceAP, int moves); /*where it moves based on the source*/
        vector<string> BFS_goal(int source, int dest); /*destination*/
    
    private:
        Graph airport_graph;
};
