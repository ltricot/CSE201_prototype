#pragma once
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <unordered_set>
#include <clocale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "boost/tokenizer.hpp"
#include "boost/algorithm/string.hpp"
#include "Eigen/Dense"

#include "primitives.hpp"
#include "driver.hpp"


class SummariesIt { 
    private:
    std::string sdata ; 
    Driver driver;
    std::vector<Paper> pKeys ; 
    SummaryAccessor sAccess;

    public:
    SummariesIt(std::string sdata);

    class iterator : public std::iterator<
            std::input_iterator_tag,
            Paper, int, const Paper*, Paper> {

        private:
        int cursor;
        SummariesIt *parent ; 
        
        public:
        iterator(SummariesIt *parent, int cursor): parent(parent), cursor(cursor) {}

        // make it so next pEde is available
        iterator operator++();

        /**
         * For it != crawler.end()?
         * This is an infinite iterator and so there is no end condition.
         */
        bool operator==(iterator other) const { return other.cursor == cursor; }
        bool operator!=(iterator other) const { return other.cursor != cursor; }

        // get next pEdge
        Paper operator*() const;
    };

    iterator begin();
    iterator end();
};

class TFIDF {
    public:
    // type of a word to paper interaction
    typedef std::tuple<std::string, Paper, double> pEdge;
    std::vector<pEdge> buffer; //object on which we iterate to get new pEdge object
    SummariesIt summaries;

    void update(int threshold);

    TFIDF(std::string sdata) : sdata(sdata), summaries(sdata) {
        update(30000); //we initialize the tfidf object with 30000 summaries
    };
    
    std::unordered_set<std::string> papers; //vector of the ids of the papers we got
    std::map<std::string, int> vocab; // set containing all the words
    Eigen::MatrixXd weightMat; // TF-IDF weighting matrix
    

    class iterator : public std::iterator<
            std::input_iterator_tag,
            pEdge, int, const pEdge*, pEdge> {
	
	private:
        TFIDF *parent;
        std::vector<pEdge>::iterator cursor;
		    
        public:
        iterator(TFIDF *parent){
            cursor = parent->buffer.begin();
        };

        // make it so next pEde is available
        iterator operator++();

        /**
         * For it != crawler.end()?
         * This is an infinite iterator and so there is no end condition.
         */
        bool operator==(iterator other) const { return false; }
        bool operator!=(iterator other) const { return true; }

        // get next pEdge
        pEdge operator*() const;
    };

    iterator begin();
    iterator end();

    private:
        std::string sdata ; // name of the driver filled by minhash, from which we read
        int counter=0; //to count the number of words and do the mapping in vocab
        std::vector<std::vector<double>> Occ2d; //iterative version of OccMat
        /*matrix whose coefficients is the number of occurences of the word of the column 
        in the corresponding document of the row */
        Eigen::MatrixXd OccMat;  //matrix whose coefficients is the number of occurences of the word of the column in the corresponding paper of the row
        Eigen::VectorXd CountDoc;
        unsigned int nrow; // matrix row number
	unsigned int ncol; // matrix column number
        std::vector<std::string> textParse(const std::string & summary); //to parse a summary
        void convertsum(const std::vector<std::string> & parsed_doc); //function that convert the data contained in a summary into Occ2d
        void calweightMat();//compute the tf-idf weight matrix
        void createOccMat(); //function that creates the OccMat 
        void createCountDoc(); //function that creates a vector that stores for each word in how many documents it appears
};
