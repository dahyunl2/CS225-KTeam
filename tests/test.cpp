#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>

/*src*/
#include "/workspaces/cs225/225_project/CS225-KTeam/src/airport.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/graph.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/BFS.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/PageRank.h"

using std::string;
using std::cout;
using std::endl;

using namespace std;


TEST_CASE("Testing Airport constructor 1")
{
    unordered_map<string, Airport> vertices;
    cout<<"Testing vector constructor with Southend airport"<<endl;
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
}


TEST_CASE("Testing Airport constructor 2") { 

    cout<<"Testing string constructor with Mount Hagen Kagamuga Airport"<<endl;
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
}

TEST_CASE("Testing Graph constructor") {
    string apData = "/workspaces/cs225/225_project/CS225-KTeam/data/airports.dat";
    string routeData = "/workspaces/cs225/225_project/CS225-KTeam/data/routes.dat";
    
    // Initialize Graph class with full airports and routes data
    Graph graph = Graph(apData, routeData);
    unordered_map<int, Airport> airportMap = graph.getVertices();

    // Pick 1 airports (Incheon International Airport)
    
    int ICN = 3930;
    
    // Check airportMap (Adjacent Matrix : V - Airports, E - Flight)
    for (auto iter = airportMap.begin(); iter != airportMap.end(); ++iter) {
        if (iter->first == ICN) {
            int id = iter->first;
            auto dest_APs = iter->second.destAPs;

            for (auto iter = dest_APs.begin(); iter != dest_APs.end(); ++iter) {
                REQUIRE(iter->second.getfromWhereId() == id);
            }
        }
    }
}


TEST_CASE("Testing Pagerank function top_N_airport()") { 
    cout << "Testing Pagerank function top_airport() - top 3 airports" << endl;
    PageRank *test = new PageRank(); 
    test->name_list.resize(5);
    test->pr_output.resize(5);

    test->name_list[0] = 0;
    test->name_list[1] = 1;
    test->name_list[2] = 2;
    test->name_list[3] = 3;
    test->name_list[4] = 4;

    test->pr_output[0] = 0.435;
    test->pr_output[1] = 323.15;
    test->pr_output[2] = 24.21;
    test->pr_output[3] = 57.33;
    test->pr_output[4] = 3.5;

    //pick top 3 airport's id
    vector<int> top_3 = test->top_N_airport(3); 
    REQUIRE(1 == top_3[0]);
    REQUIRE(3 == top_3[1]);
    REQUIRE(2 == top_3[2]);
}

TEST_CASE("Testing constructing graph from a subset of data and execute pagerank algorithm on the test data set") { 
    string airportFile = "/workspaces/cs225/225_project/CS225-KTeam/tests/airports_test_pr.dat";
    string routesFile = "/workspaces/cs225/225_project/CS225-KTeam/tests/route_test_pr.dat";


    Graph airportGraph(airportFile, routesFile);
    auto airportMap = airportGraph.getVertices();

    PageRank *page = new PageRank();
    airportGraph.adjMatrix(page);
    page->make_adj(page->dim, 0.85);
    vector<double> initial = page->initial_vector();
    page->rank(initial, 150, true);
    vector<int> id_rank = page->top_N_airport(2);

    REQUIRE(3364 == id_rank[0]);
    REQUIRE(3728 == id_rank[1]);
}