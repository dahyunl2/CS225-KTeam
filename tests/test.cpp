#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>

/*src*/
#include "/workspaces/cs225/225_project/CS225-KTeam/src/airport.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/graph.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/BFS.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/djikstras.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/PageRank.h"

using std::string;
using std::cout;
using std::endl;

using namespace std;


TEST_CASE("Testing Airport constructor 1")
{
    unordered_map<string, Airport> vertices;
    cout<<"\n\n **Testing vector constructor with Southend airport**\n"<<endl;
    vector<string> airport_data = {"508","Southend Airport","Southend","United Kingdom", "", "", "51.5713996887207", "0.6955559849739075"};
    vertices["Southend Airport"] = Airport(airport_data);
    int ID = vertices["Southend Airport"].getAPID();
    string Name = vertices["Southend Airport"].getAPName();
    string City = vertices["Southend Airport"].getAPCity();
    string Country = vertices["Southend Airport"].getAPCountry();
    int Latitude = (int)vertices["Southend Airport"].getAPLat();
    int Longitude = (int)vertices["Southend Airport"].getAPLong();

    REQUIRE(508 == ID);
    REQUIRE("Southend Airport" == Name);
    REQUIRE("Southend" == City);
    REQUIRE("United Kingdom" == Country);
    REQUIRE(51 == Latitude);
    REQUIRE(0 == Longitude);
    cout << ID << ", " << Name << ", " << City << ", " << Country << ", " << Latitude << ", " << Longitude << endl;

}

TEST_CASE("Testing Airport constructor 2") { 

    cout<<"\n\n **Testing string constructor with Mount Hagen Kagamuga Airport**\n"<<endl;
    unordered_map<string, Airport> vertices;
    string mount_hagen = "1,\"Mount Hagen Kagamuga Airport\",\"Mount Hagen\",\"Papua New Guinea\",\"HGU\",\"AYMH\",-5.826789855957031,144.29600524902344,5388,10,\"U\",\"Pacific/Port_Moresby\",\"airport\",\"OurAirports\"";
    vertices["Mount Hagen Kagamuga Airport"] = Airport(mount_hagen);
    int ID = (vertices["Mount Hagen Kagamuga Airport"].getAPID());
    string Name = (vertices["Mount Hagen Kagamuga Airport"].getAPName());
    string City = (vertices["Mount Hagen Kagamuga Airport"].getAPCity());
    string Country = (vertices["Mount Hagen Kagamuga Airport"].getAPCountry());
    int Latitude = (int)vertices["Mount Hagen Kagamuga Airport"].getAPLat();
    int Longitude = (int)vertices["Mount Hagen Kagamuga Airport"].getAPLong();
    
    REQUIRE(1 == ID);
    REQUIRE("Mount Hagen Kagamuga Airport" == Name);
    REQUIRE("Mount Hagen" == City);
    REQUIRE("Papua New Guinea" == Country);
    REQUIRE(-5 == Latitude);
    REQUIRE(144 == Longitude);
    
    cout << ID << ", " << Name << ", " << City << ", " << Country << ", " << Latitude << ", " << Longitude << endl;


}

TEST_CASE("Testing Graph constructor") {
    string aData = "/workspaces/cs225/225_project/CS225-KTeam/data/airports.dat";
    string rData = "/workspaces/cs225/225_project/CS225-KTeam/data/routes.dat";

    Graph aGraph = Graph(aData, rData);
    unordered_map<int, Airport> aMap = aGraph.getVertices();

    // Airport ID of Incheon International Airport and Yangyang International Airport
    int ICN = 3930;
    int YY = 6006;

    cout << "\n\n **Testing all the adjacent airports and the corresponding flights of international airports in Korea**\n" << endl;
    // Expected: All the adjacent airports and the corresponding flights of international airports in Korea

    for (auto it = aMap.begin(); it != aMap.end(); ++it) {
        if (it->first == ICN || it->first == YY) {
            
            int id = it->first;
            cout << "Flight departing from " << it->second.getAPID() << ", ";
            cout << it->second.getAPName() << ", ";
            cout << it->second.getAPCity() << endl;

            unordered_map<int, Flight> dest_APs = it->second.destAPs;
            
            cout << "dest AP size: " << dest_APs.size() << endl;
            for (auto it = dest_APs.begin(); it != dest_APs.end(); ++it) {
                REQUIRE(it->second.getfromWhereId() == id);
                cout << "Flight departing from " << it->second.getfromWhereId() << endl;
                cout << "Flight arriving at " << it->second.gettoWhereId() << endl;
                cout << "Flight distance: " << it->second.getDistance() << endl;
            }
        }
    }
}

TEST_CASE("Testing the traversed airports in BFS") {

    string aData = "/workspaces/cs225/225_project/CS225-KTeam/data/airports.dat";
    string rData = "/workspaces/cs225/225_project/CS225-KTeam/data/routes.dat";

    BFS bfs(aData, rData);
    
    cout << "\n\n **Testing all BFS traversals starting from John F Kennedy International Airport**\n" << endl;
    // Expected: all BFS traversals starting from John F Kennedy International Airport

    int JFK = 3797;
    vector<string> all_traversals = bfs.BFS_move(JFK, 30);
    for(unsigned i = 0; i < all_traversals.size(); i++){
        cout << all_traversals[i] ;
        if (i == all_traversals.size()-1) {
            cout << "  END" << endl;
        } else {
            cout << " ==> ";
        }
        if(i % 5 == 0 && i != 0)
            cout << endl;
    }
}


TEST_CASE ("Testing Djikstra's algorithm to find the shortest path") { 

    cout << "\n\n **Testing the shortest path between Charles de Gaulle International Airport to Vancouver International Airport using Djikstra's algorithm**\n" << endl;
    
    string aData = "/workspaces/cs225/225_project/CS225-KTeam/data/airports.dat";
    string rData = "/workspaces/cs225/225_project/CS225-KTeam/data/routes.dat";

    string start;
    string destination;

    Graph aGraph(aData, rData);
    Djikstras shortestPath = Djikstras(aGraph, "Charles de Gaulle International Airport", "Vancouver International Airport");
    
    double d = shortestPath.getMinDist();
    vector<string> path = shortestPath.getVertices();

    // Expected: Find the shortest path between University of Illinis Willard Airport to Incheon International Airport using Djikstra's algorithm

    cout << "path size: "<< path.size() << endl;
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

TEST_CASE("Testing Pagerank function top_airport()") { 
    cout << "\n\n **Testing Pagerank function top_airport()**\n" << endl;
    //construct a pagerank obj, manually setup the name_list and pr_result
    PageRank *test = new PageRank(); 
    test->name_list.resize(5);
    test->pr_output.resize(5);

    test->name_list[0] = 0;
    test->name_list[1] = 1;
    test->name_list[2] = 2;
    test->name_list[3] = 3;
    test->name_list[4] = 4;

    test->pr_output[0] = 0.245;
    test->pr_output[1] = 324.15;
    test->pr_output[2] = 23.21;
    test->pr_output[3] = 56.33;
    test->pr_output[4] = 4;

    //pick out the top 3 airport's id
    vector<int> rank = test->top_N_airport(3); 
    REQUIRE(1 == rank[0]);
    REQUIRE(3 == rank[1]);
    REQUIRE(2 == rank[2]);
}

TEST_CASE("Testing Pagerank implementation on a subset of the whole data set") { 
    //adjust the precision of the weight of edge to be shown
    //cout << setprecision(10);
    cout << "\n\n **Testing constructing graph from a subset of data and pagerank on the data set**\n" << endl;
    string airportFile = "/workspaces/cs225/225_project/CS225-KTeam/tests/airports_test_pr.dat";
    string routesFile = "/workspaces/cs225/225_project/CS225-KTeam/tests/route_test_pr.dat";
    Graph airportGraph(airportFile, routesFile);
    auto airportMap = airportGraph.getVertices();

    PageRank *page = new PageRank();
    airportGraph.adjMatrix(page);
    page->make_adj(page->num, 0.85);
    page->print_adj();
    vector<double> initial = page->initial_vector();
    vector<double> re = page->rank(initial, 100, true);
    page->print_result();
    vector<int> id_rank = page->top_N_airport(3);

    REQUIRE(3364 == id_rank[0]);
    REQUIRE(3728 == id_rank[1]);
}