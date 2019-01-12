#include <iostream>
#include <vector>
#include <map>

#include "primitives.hpp"
#pragma once

//the minhash algorithms is designed to compute similarities between authors in a fast way
//to do so, it takes sets of articles to which we assign numerical IDs
//the whole idea is avoid comparing the full set of articlew from two authors, which would take a lot of time on big scales
//instead, we take the articles ID and simulate permutations of their order through hash functions of the for a*articleID+b
//then we build a signature for the author, corresponding to the minimum value obtained for each hash function
//we then compare different authors' signatures to compute their similarity
//we thus only do k (= number of hash functions) comparisons, which give a very good approximation of the similarity between authors 
//for more details, look here: 

class MinHash {
    private:

    typedef std::vector<int> vector;

    unsigned int hash_nb; //number of hash functions generated
    unsigned int MaxArticleID = 1500000; //the maximum value that an article can get
    unsigned int prime = 1500007; //smallest prime number bigger than MacArticleID
    unsigned int counter = 0; //counter used to assign numerical values to articles
    std::map<Author, std::vector<Paper>> users2articles; //map that associates each author to a vector of the papers he has cited
    std::map<Paper, int> article2int; //map that associates each article to a numerical ID

    std::vector<int> hashes_a; //vector of the a coefficients of my hash functions
    std::vector<int> hashes_b; //vector of the b coefficients of my hash functions

    public:

    //creates random coefficients for the hash functions (rank = nb of hash functions)
    MinHash(int rank);

    //compute one user's signature by computing hash functions
    std::vector<int> getSignature(Author author);

    //computes the similarity between 2 authors
    float getSimilarity(Author author1, Author author2);

    //adds the author to the users2articles map if he was never seen
    //adds paper to the image of my user by the users2articles map if it is not already in it
    //adds the paper to the articles2int map and gives him a numerical ID if it was never seen
    void update(Edge edge);
    
};