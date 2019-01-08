#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Eigen/Dense"

class tfidf {

    public:
        Eigen::MatrixXd weightMat; // TF-IDF weighting matrix
	    tfidf(int argc, char *argv[]) { //constructor pb: ne pas mettre d'argument ??
		    calweightMat(argc,argv);
	    }
    
    private:
        //iterative part
        int counter=0; //to count the number of words and do the mapping in vocab
        std::map<std::string, int> vocab; // set containing all the words
        std::vector<std::vector<int>> Occ2d; //iterative version of OccMat
        void update(const std::vector<std::string> & parsed_doc); //function that update vocab and Occ2d in real time
        void reader(int argc, char *argv[]); //function that get the abstract, parse them and then treat them with update()

        //non-iterative part

        /*matrix whose coefficients is the number of occurences of the word of the column 
        in the corresponding document of the row */
        Eigen::MatrixXd OccMat; 
        
        Eigen::VectorXd CountDoc;
        unsigned int nrow; // matrix row number
	    unsigned int ncol; // matrix column number

        void createOccMat();

        /*function that creates a vector that stores for each word in how many documents it appears*/
        void createCountDoc(); 

        void calweightMat(); //compute the tf-idf weight matrix

};