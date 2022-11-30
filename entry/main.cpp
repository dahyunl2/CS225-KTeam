#include "Flight.h"
#include "airport.h"
#include <iostream>
#include <fstream>

using namespace std;
int main () {
    ifstream f("/workspaces/cs225/225_project/CS225-KTeam/entry/airports.dat");
    string line;

    if (f.is_open()) {
        // cout << "open" << endl;
        while (getline(f, line)) {
                // cout << "while" << endl;

            Airport a = Airport(line);
            // cout << "-------" << endl;
            // if (a.)
            // cout << a.getAPID() << a.getAPName() << a.getAPCity() << a.getAPCountry() << z.getAPLat() << a.getAPLong()<<endl;
        }
    }
}
