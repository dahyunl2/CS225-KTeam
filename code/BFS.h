#pragma once
#include "airport_graph.h"
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
        vector<string> BFS_All(int source);
        vector<string> BFS_move(int sourceAP, int moves);
        vector<string> BFS_goal(int source, int dest);
    
    private:
        Graph airport_graph;
};