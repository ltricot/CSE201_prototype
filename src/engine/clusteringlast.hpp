#pragma once
#include "Eigen/Dense"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <cstdlib> 
#include <ctime>
#include <set>
#include <algorithm>
#include <random>
#include <vector>

#include "primitives.hpp"

class Cluster {
    public:
    std::map<int,std::vector<string>> clusters; //output a map that associates to each label its cluster of authors 
    Cluster(std::vector<Friends> & similarities) { //constructor
        findneighbors(similarities);
        sizeInput=nodes.size();
        createcluster();
    }

    private:
    int sizeInput; //size of the input vector
    static int T; // temperature
    /* "label" is a std::vector that associates to each vector of the input (each node) its label ie the label at index i is the label of the ith vector*/
    std::vector<int> label;
    std::map<string,int> nodes; //map from Author to int
    std::map<int,string> nodesindex //map from int to Author
    std::vector<std::vector<std::pair<int,double>>> neighbors; // vector that at index i contains a map that associates to each neighbors of i its similarity with i
    double updaterate ; //save the rate of updated labels 
    void findneighbors(std::vector<Friends> & similarities); //find the neighbors for each nodes
    void initializelabel(); //function to initialize label such that each vector has a different label
    std::vector<std::vector<double>> allCDF; //vector that save the cdf of the probability to choose a certain neighbor for the vector at index i
    void getCDF(); //create the vector allCDF
    int getMaxSim(int & i ); //function that given a vector index (a node) return the node with which it has the greatest similarity with a big probability
    void updatelabel(int order[]); //function that updates the labels during a propagation
    void createcluster(); //function that do the clustering

    
};

std::vector<int> getKeys(std::string folder);
std::vector<Author> getNeighbors(std::string folder, int label);
