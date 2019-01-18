#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Eigen/Dense"
#include <set>

class cluster{
    public: 
    std::vector<int> label;
    cluster(std::vector<std::vector<int>> & input) { //constructor
        sizeInput =input.size();
        nodes = input;
        initlabel();
        propagate();
    }

    private:
        int sizeInput;
        std::vector<std::vector<int>> nodes;
        void initlabel(); //initialize the labels: each node has a different one
        int most_freq(int & i); // function that returns for a given index vector the most popular label among its neighbors
        void propagate(); // function that proceeds the label propagation
};