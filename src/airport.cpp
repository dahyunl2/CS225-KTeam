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


 //helper functions for data parsing

 //erase whitespaces left and right side of string
std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

//split the line with the given separator and returns the number of sliced elements
int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

//constructor with each line from airport data file
// split using delimiter ',', store each data in vector, and assign the matching data to the variable
Airport::Airport(string& line) {
            vector<string> ap_vec;
            unsigned s = SplitString(line, ',', ap_vec);
            for (unsigned i = 0; i < s; i++) {
                ap_vec[i] = Trim(ap_vec[i]);
            }
            if (ap_vec.size() == 14) {
                ap_id = stoi(ap_vec[0], nullptr);
                ap_name = ap_vec[1].substr(1, ap_vec[1].size() - 2);
                ap_city = ap_vec[2].substr(1, ap_vec[2].size() - 2);
                ap_country = ap_vec[3].substr(1, ap_vec[3].size() - 2);
                //change string to int/double if necessary
                ap_lat = stod(ap_vec[6], nullptr);
                ap_long = stod(ap_vec[7], nullptr);
            }
                
            // try {
            //     ap_lat = stod(ap_vec[6], nullptr);
            // }
            // catch(const std::exception& e) {
            //     cout << ap_vec[6] << endl;
            //     cout << e.what() << endl;
            // };
            
            // try {ap_long = stod(ap_vec[7], nullptr);}
            // catch(const std::exception& e) {
            //     cout << ap_vec[7] << endl;
            //     cout << e.what() << endl;
            //     // break;
            // }
    //     }
    // } 
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

