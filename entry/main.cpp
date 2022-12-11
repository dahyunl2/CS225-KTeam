
#include "/workspaces/cs225/225_project/CS225-KTeam/src/airport.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/graph.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/BFS.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/djikstras.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/PageRank.h"

using std::string;
using std::cout;
using std::endl;

using namespace std;int main () {
    string aData = "/workspaces/cs225/225_project/CS225-KTeam/data/airports.dat";
    string rData = "/workspaces/cs225/225_project/CS225-KTeam/data/routes.dat";

    string start;
    string destination;

    Graph aGraph(aData, rData);
    unordered_map<int, Airport> aMap = aGraph.getVertices();
    BFS bfs(aData, rData);



    // Testing Graph; insert the id of airport to run
    int id1 = 1111;
    int id2 = 2222;

    cout << "inserted ids for checking adjacent airports: " << id1 << ", " << id2 << endl;

    for (auto it = aMap.begin(); it != aMap.end(); ++it) {
        if (it->first == id1 || it->first == id2) {
            
            int id = it->first;
            cout << "Flight departing from " << it->second.getAPID() << ", ";
            cout << it->second.getAPName() << ", ";
            cout << it->second.getAPCity() << endl;

            unordered_map<int, Flight> dest_APs = it->second.destAPs;
            
            cout << "dest AP size: " << dest_APs.size() << endl;
            for (auto it = dest_APs.begin(); it != dest_APs.end(); ++it) {
                cout << "Flight departing from " << it->second.getfromWhereId() << endl;
                cout << "Flight arriving at " << it->second.gettoWhereId() << endl;
                cout << "Flight distance: " << it->second.getDistance() << endl;
            }
        }
    }


    // Testing BFS; insert the ids of starting and destination airports to run
    int id_bfs1 = 3797;
    int id_bfs2 = 3000;

    cout << "inserted ids for checking traversed airports using bfs: " << id_bfs1 << ", " << id_bfs2 << endl;

    vector<string> all_traversals = bfs.BFS_goal(id_bfs1, id_bfs2);
    for(unsigned i = 0; i < all_traversals.size(); i++){
        cout << all_traversals[i] ;
        if (i == all_traversals.size()-1) {
            cout << "  END" << endl;
        } else {
            cout << " ==> ";
        }
        if (i % 5 == 0 && i != 0)
            cout << endl;
    }


    // Testing Djikstras; insert the names of starting and destination airports to run

    string starting = "Charles de Gaulle International Airport";
    string dest = "Vancouver International Airport";

    cout << "inserted airport names for checking shortest path using djikstras: " << starting << ", " << dest << endl;
    Djikstras shortestPath = Djikstras(aGraph, starting, dest); 
    double d = shortestPath.getMinDist();
    vector<string> path = shortestPath.getVertices();

    cout <<"Visited Airport \n"<<endl;

    for (unsigned i = 0; i < path.size(); i++) {
        cout << path[i] ;
        if (i == path.size() - 1) {
            cout << "  END" << endl;
        }
        if (i != path.size() - 1) 
            cout << "==>" << endl;

        if (i % 5 == 0 && i != 0)
            cout << endl;
    }

}
