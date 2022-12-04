#include <iostream>
#include "PageRank.h"
#include <vector>
#include <numeric>
#include <math.h>


/**
*	modify adjmatrix according to damping factor, set num of the pagerank obj
*	@param num dimention of matrix to be set and stored
*   @param damping damping factor
*/
void PageRank::make_adj(int num, double damping) {
    this->num = num;//store num
    //resize adj matrix
    //adj.resize(num,vector<double>(num));

    //use damping factor to generate the require extra factor
    double d_factor = (1-damping)/num;

    //adjust adj matrix according to pagerank alg
    for(int i = 0; i < num; i++){
        double sum = 0;
        for(int j = 0; j < num; j++){
            sum += adj[j][i];
        }     
        if(sum == 0){
            //double z = 1/this->num;
            for(int j = 0; j < num; j++){
                adj[j][i] = 1/(double)num;
            }              
        } else {
            for(int j = 0; j < num; j++){
                adj[j][i] = (adj[j][i]/sum)*damping+d_factor;
            }             
        }
    }
}


/**
*	execute pagerank algorithm 
*	@param initial starting vector
*   @param time time of iteration
*   @param normalize whether to perform normalization or not
*   @return the result vector
*/
vector<double> PageRank::rank(vector<double> initial, int time, bool normalize) {
    //vectors which stores the intermediate result
    vector<double> tmp = initial;
    vector<double> tmp2 = initial;
    for(int t = 0; t < time; t++){
        for(int i = 0; i < num; i++){
            //initialize the vector
            tmp2[i] = 0;
            //calculate product of adjmatrix and vector 
            for(int j = 0; j < num; j++){
                tmp2[i] += adj[i][j] * tmp[j];

                if(normalize) {
                    double sum = 0;
                    //perform norm 2 normalize
                    for(std::vector<double>::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
                        sum += (*it)*(*it);
                    double normalize = sqrt(sum);

                    for(int n = 0; n < num; n++){
                        tmp2[n] = tmp2[n] / normalize;
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
        for(auto it = pr_output.begin(); it != pr_output.end(); ++it){
            if(*it > max){
                bool flag = true;
                //check if the current airport is already on the list of the important airport
                for(auto temp = largest.begin(); temp != largest.end(); ++temp){
                    if(*temp == *it) {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                    max = *it;
            }
        }
        largest[position] = (max);
        position++;
    }

    position = 0;
    //using the index and the name_list to find out the relating airport id
    for(int i = 0; i < num; i++){
        int count = 0;
        for(auto it = pr_output.begin(); it != pr_output.end(); ++it){
            if(largest[i] == *it){
                airport[position] = (name_list[count]);
                position++;
            }
            count++;
        }
    }

    //print the id
    cout<<"top "; 
    cout<<num; 
    cout<<" important airport\n"; 
    for(int i = 0; i < num; i++){
        cout<<airport[i];
        cout<<"\n";
    }
    return airport;
}



/**
*	generates the starting vector
*   @return the starting vector for pagerank
*/
vector<double> PageRank::initial_vector(){
    vector<double> initial;
    initial.resize(this->num);
    for(int i = 0; i < this->num; i++){
        initial[i] = rand();
    }
    return initial;
}

/**
*	print the adj matrix. column and row are labeled
*/
void PageRank::print_adj(){
    cout<<"adj matrix"<<endl;
    cout<<"      ";
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<"           ";
    }
    cout<<"\n";
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<"  ";
        for(int j = 0; j < this->num; j++){
            cout<<this->adj[i][j];
            cout<<"  ";
        } 
        cout<<"\n";
    }
    cout<<"\n";
}

/* 
*	effect: print the result vector. airport ids are also labeled
*/
void PageRank::print_result(){
    cout<<"page rank result\n"; 
    cout<<" ID      value\n"; 
    for(int i = 0; i < this->num; i++){
        cout<<this->name_list[i];
        cout<<" ";
        cout<<this->pr_output[i];
        cout<<"\n";
    }
    cout<<"\n";
}

