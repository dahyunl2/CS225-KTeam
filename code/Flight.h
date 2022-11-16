#pragma once

class Flight {
    public:
        Flight();
        //constructor without distance
        Flight(int from, int to);
        Flight(int from, int to, double dist);

        //setters
        void setfromWhere(double from);
        void settoWhere(double to); 
        void setDistance(double dist);

        //getters
        int getfromWhereId();       
        int gettoWhereId();         
        double getDistance();
       

        //operator overloading
        //"==" checking if two edges(path) are the same
        bool operator==(Flight& other) const;
        //"<" comparing distance between edges
        bool operator<(const Flight& other) const;

    private:
        //ID of airport coming from
        int fromWhereId;
        //ID of airport going to
        int toWhereId;
        //distances between two airports in (km)
        double distance;
};