#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>

/*src*/
#include "/workspaces/cs225/225_project/CS225-KTeam/src/airport.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/graph.h"
#include "/workspaces/cs225/225_project/CS225-KTeam/src/BFS.h"

using std::string;
using std::cout;
using std::endl;

using namespace std;


TEST_CASE("Testing Airport constructor with vector")
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


TEST_CASE("Testing Airport constructor with string") { 

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