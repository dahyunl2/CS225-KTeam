#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Flight.h"

using namespace std;

class Airport {
    public:
        //constructors
        Airport();
        Airport(string& line);
        Airport(vector<string> ap_vec);    
        Airport(int id, string name, string city, string country, double lat, double long);
        
        // unordered_map<int, Flight> destAPs;

        int getAPID();
        string getAPName();
        string getAPCity();
        string getAPCountry();
        double getAPLat();
        double getAPLong();

    private:
        int ap_id;
        string ap_name;
        string ap_city;
        string ap_country;
        double ap_lat;
        double ap_long;
        
};
