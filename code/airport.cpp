#include "Airport.h"

using namespace std;

//default constructor
Airport::Airport() {
    ap_id = 0;
    ap_name = "";
    ap_city = "";
    ap_country = "";
    ap_lat = 0.0;
    ap_long = 0.0;
}

//constructor with inputs
Airport::Airport(int id, string name, string city, string country, double latitude, double longitude) 
    : ap_id(id), ap_name(name), ap_city(city), 
    ap_country(country), ap_lat(latitude), ap_long(longitude) {}

//helper function to split string in data file
vector<string> tokenize(string str, char delimiter) {
    vector<string> output;
    string temp = "";

    for (unsigned i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            output.push_back(temp);
            temp = "";
        } else {
            temp += str[i];
        }
    }
    output.push_back(temp);
    return output;
}

//erase first and last substring from the string
void eraseSubStr(std::string& str) {
    str.erase(0, 1);
    str.erase(str.size() - 1);
}

//constructor with each line from airport data file
// split using delimiter ',', store each data in vector, and assign the matching data to the variable
Airport::Airport(string& line) {
    vector<string> ap_vec = tokenize(line, ',');
 
    //change string to int/double if necessary
    ap_id = stoi(ap_vec[0], nullptr);
    ap_name = ap_vec[1].substr(1, ap_vec[1].size() - 2);
    ap_city = ap_vec[2].substr(1, ap_vec[2].size() - 2);
    ap_country = ap_vec[3].substr(1, ap_vec[3].size() - 2);
    ap_lat = stod(ap_vec[6], nullptr);
    ap_long = stod(ap_vec[7], nullptr);
}


//vector constructor with a vector with data
Airport::Airport(vector<string> ap_vec){
    ap_id = stoi(ap_vec[0], nullptr);
    ap_name = ap_vec[1];
    ap_city = ap_vec[2];
    ap_country = ap_vec[3];
    ap_lat = stod(ap_vec[6], nullptr);
    ap_long = stod(ap_vec[7], nullptr);
}


//getter for each variable
int Airport::getAPID() {
    return ap_id;
}
string Airport::getAPName() {
    return ap_name;
}
string Airport::getAPCity() {
    return ap_city;
}
string Airport::getAPCountry() {
    return ap_country;
}
double Airport::getAPLat() {
    return ap_lat;
}
double Airport::getAPLong() {
    return ap_long;
}

