#pragma once
#include "Eigen/Dense"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <cstdlib> 
#include <ctime>


class cluster {
    public:
    /* "label" is a std::vector that associates to each vector of the input (each node) its label ie the label at index i is the label of the ith vector*/
    std::vector<int> label;
    cluster(std::vector<Eigen::VectorXd> & input) { //constructor
        createcluster(input);
    }

    private:
    std::vector<Eigen::VectorXd> nodes; //to store the input vector
    int sizeInput; //size of the input vector
    static int T; // temperature
    static int K; //number of neighbors for each nodes
    std::vector<std::map<int,double>> neighbors; // vector that at index i contains a map that associates to each K closest neighbors of i its similarity with i
    float updaterate ; //save the rate of updated labels 
    void findneighbors(); //find the K closest neighbors for each nodes
    void initializelabel(); //function to initialize label such that each vector has a different label

    int getMaxSim(int & i ); //function that given a vector index (a node) return the node with which it has the greatest similarity with a big probability
    void updatelabel(); //function that updates the labels during a propagation
    void createcluster( std::vector<Eigen::VectorXd> & input); //function that do the clustering

    
};