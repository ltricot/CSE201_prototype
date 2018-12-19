#include <iostream>
#pragma once

#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include "Eigen/Dense"

class tfidf{
    public:
        Eigen::MatrixXd weightMat; // TF-IDF weighting matrix
	    tfidf(std::vector<std::vector<std::string>> & input):SetofDocs(input) { //constructor
		    calweightMat();
	    }

    private:
        std::vector<std::vector<std::string>> SetofDocs; //set of all the summaries
        std::vector<std::string> vocabList; // set containing all the words

        /*matrix whose coefficients is the number of occurences of the word of the column 
        in the corresponding document of the row */
        Eigen::MatrixXd OccMat; 
        Eigen::VectorXd CountDoc;
        unsigned int nrow; // matrix row number
	    unsigned int ncol; // matrix column number
        //Eigen::VectorXd numOfTerms; //vector which stores the number of words in a doc

        void createVocabList(); //function that creates the vocabList

        /* function that for a given document create a vector that stores the number of occurences
        of the words in VocabList*/
        Eigen::VectorXd countOccDoc(const std::vector<std::string> & doc); 
        void createOccMat(); //function that creates the OccMat 

        /*function that creates a vector that stores for each word in how many documents it appears*/
        void createCountDoc(); 

        void calweightMat(); //compute the tf-idf weight matrix

};