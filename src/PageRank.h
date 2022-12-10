#pragma once

#include <vector>
using namespace std;


class PageRank
{
  public:
    //the adj matrix for pagerank
    vector<vector<double>> adj; 

    //dimension of the dataset
    int dim;

    //the namelist of the airport id
    vector<int> name_list; 

    //the pagerank result
    vector<double> pr_output; 



    //generate random vector with the number of dimmension
    vector<double> initial_vector();

    // adjust matrix with damping factor
    void make_adj(int dim, double damping);

    //perform pagerank
    vector<double> rank(vector<double> initial, int time, bool normalize);

    //function that returns the most important airport
    vector<int> top_N_airport(int num);
};