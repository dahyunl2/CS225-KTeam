#pragma once

#include <vector>
using namespace std;


//pagerank class
class PageRank
{
  public:
    //adjust adj matrix

    void make_adj(int num, double damping);

    //perform pagerank
    vector<double> rank(vector<double> initial, int time, bool normalize);

    //pick out the most important airport
    vector<int> top_N_airport(int num);

    //generate starting vector for pagerank
    vector<double> initial_vector();

    //print adjmatrix
    void print_adj();

    //print the result vector
    void print_result();

    //the adj matrix variable for pagerank
    vector<vector<double>> adj; 

    //the namelist of the airport. contains the airport id
    vector<int> name_list; 

    //the pagerank result
    vector<double> pr_output; 

    //dimension of the adj matrix, namelist, initial vector and result vector
    int num;
};