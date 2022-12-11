#include <iostream>
#include "PageRank.h"
#include <vector>
#include <numeric>
#include <math.h>


/**
*	generates the starting random vector
*   @return the starting vector for pagerank
*/
vector<double> PageRank::initial_vector(){
    vector<double> initial;
    initial.resize(this->dim);
    for(int i = 0; i < this->dim; i++){
        initial[i] = rand();
    }
    return initial;
}

/**
*	modify adjmatrix according to damping factor, set num of the pagerank obj
*	@param dim dimention of matrix to be set and stored
*   @param damping damping factor
*/
void PageRank::make_adj(int dim, double damping) {
    this->dim = dim;//assign dim
    //use damping to acquire extra factor
    double d_factor = (1-damping)/dim;

    //fixing adj property for pagerank alg
    for(int i = 0; i < dim; i++){
        double sum = 0;
        for(int j = 0; j < dim; j++){
            sum += adj[j][i];
        }
        if(sum == 0){
            for(int j = 0; j < dim; j++){
                adj[j][i] = 1/(double)dim;
            }              
        } else {
            for(int j = 0; j < dim; j++){
                adj[j][i] = (adj[j][i]/sum)*damping+d_factor;
            }             
        }
    }
}

/**
*	execute pagerank algorithm 
*	@param initial starting vector
*   @param num_iter num_iter of iteration
*   @param is_normal whether to perform normalization or not
*   @return the result vector
*/
vector<double> PageRank::rank(vector<double> initial, int num_iter, bool is_normal) {
    //vectors which stores the intermediate result
    vector<double> tmp = initial;
    vector<double> tmp2 = initial;
    for(int t = 0; t < num_iter; t++){
        for(int i = 0; i < dim; i++){
            //vector initialize
            tmp2[i] = 0;
            //calculate product of adjmatrix and vector 
            for(int j = 0; j < dim; j++){
                tmp2[i] += adj[i][j] * tmp[j];
                if(is_normal) {
                    double sum = 0;
                    //perform norm 2 normalize
                    for(auto iter = tmp2.begin(); iter != tmp2.end(); ++iter)
                        sum += (*iter)*(*iter);
                    double is_normal = sqrt(sum);

                    for(int n = 0; n < dim; n++){
                        tmp2[n] = tmp2[n] / is_normal;
                    }
                }
            }     
        }
        tmp = tmp2;
}
    pr_output = tmp;
    return tmp;
}








/**
*	return the top N most visited airport and print the id of the top N most visited airport
*	@param num size of returning vector
*   @return the vector contains id of the top num important airport
*/
vector<int> PageRank::top_N_airport(int num){
    vector<int> airport;
    vector<double> largest;
    largest.resize(num);
    airport.resize(num);

    int position = 0;

    //figure out the index of the important airport in the pagerank result vector
    for(int i = 0; i < num; i++){
        double max = 0;
        for(auto iter = pr_output.begin(); iter != pr_output.end(); ++iter){
            if(*iter > max){
                bool insert = true;
                //check if the current airport is already on the list of the important airport
                for(auto temp = largest.begin(); temp != largest.end(); ++temp){
                    if(*temp == *iter) {
                        insert = false;
                        break;
                    }
                }
                if(insert)
                    max = *iter;
            }
        }
        largest[position] = (max);
        position++;
    }

    position = 0;
    //using the index and the name_list to find out the relating airport id
    for(int i = 0; i < num; i++){
        int count = 0;
        for(auto iter = pr_output.begin(); iter != pr_output.end(); ++iter){
            if(largest[i] == *iter){
                airport[position] = (name_list[count]);
                position++;
            }
            count++;
        }
    }

    return airport;
}




