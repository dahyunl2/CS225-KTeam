#include "Flight.h"
#include <string>

using namespace std;

Flight::Flight(){
    fromWhereId=-1;
    toWhereId=-1;
    distance=2147483647; //Which is possible max of int variable
}
//constructor without distance
Flight::Flight(int from, int to){
    fromWhereId=from;
    toWhereId=to;
    distance=2147483647;
}
Flight::Flight(int from, int to, double dist){
    fromWhereId=from;
    toWhereId=to;
    distance=dist;
}

//setters
void Flight::setfromWhere(double from){
    fromWhereId=from;
}
void Flight::settoWhere(double to){
    toWhereId=to;
}
void Flight::setDistance(double dist){
    distance=dist;
}

//getters
int Flight::getfromWhereId(){
    return fromWhereId;
}      
int Flight::gettoWhereId(){
    return toWhereId;
}        
double Flight::getDistance(){
    return distance;
}


//operator overloading
//"==" checking if two edges(path) are the same
bool Flight::operator==(Flight& other) const{
    if(fromWhereId==other.fromWhereId && toWhereId==other.toWhereId){
        return true;
    }
    return false;
}
//"<" comparing distance between edges
bool Flight::operator<(const Flight& other) const{
    if(distance<other.distance){
        return true;
    }
    return false;
}