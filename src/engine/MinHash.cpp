#include <iostream>
#include <vector>
#include <unordered_map>

#include "MinHash.hpp"
#pragma once
#include <random>

int random_int() {
    // function that generates a random integer between 0 and 1500000
    int min = 0;
    int max = 1500000;
    std::random_device rd;     // used once to initialise engine
    std::mt19937 rng(rd());    // random-number engine
    std::uniform_int_distribution<int> uni(min,max);

    int random_integer = uni(rng);
    return random_integer;
}

MinHash::MinHash(int rank)
{
    //creates random coefficients for the hash functions (rank = nb of hash functions)
    hash_nb = rank;
    int k = rank;
    int a = 0;
    while (k > 0){
        int a = random_int();
        if (std::find(hashes_a.begin(), hashes_a.end(), a) != hashes_a.end()){
            hashes_a.push_back(a);
            k -= 1;
        };
    };
    
    while (rank > 0){
        int b = random_int();
        if (std::find(hashes_b.begin(), hashes_b.end(), b) != hashes_b.end()){
            hashes_b.push_back(b);
            rank -= 1;
        };
    };
}

std:: vector<int> MinHash::getSignature(const Author &author)
{
    //returns the minhash signature of my author 
    std::vector<int> user_signature;
    //for each hash function
    for (int i = 0; i < hash_nb; i++){
        //initialize the minimum value to a large value that will never be obtained
        int minhash = prime + 1;
        //for each article cited by the author
        //users2articles.find(author);
        std::vector<Paper> paperVector = users2articles[author.name];
        for (int j = 0; j < paperVector.size(); j++){
            //get the numerical ID of the article
            int article_nb = article2int[users2articles[author.name][j].id];
            //hash this value (corresponds to a permutation)
            int hash_value = (article_nb*hashes_a[i]+hashes_b[i])%prime;
            if (hash_value < minhash){
                //update the value of minhash if the hash_value is lower than the current minhash
                minhash = hash_value;
            }
        }
        user_signature.push_back(minhash);
    }
    return user_signature;
}

float MinHash::getSimilarity(const Author &author1, const Author &author2){
    //computes the similarity between 2 authors
    int count = 0;
    std::vector<int> signature1 = getSignature(author1);
    std::vector<int> signature2 = getSignature(author2);
    for (int i = 0; i < hash_nb; i++){
        if (signature1[i]==signature2[i]){
            count += 1;
        }
    }
    return count/hash_nb;
}

void MinHash::update(Edge edge)
{
    // if the edge.author not in keys of users2articles, add it to users2articles
    // if the paper not in keys of articles2int, add it to article2int using the counter
    // add the paper to the vector at users2articles[user]

    std::pair <std::unordered_map<std::string, std::vector<Paper> > ::iterator, bool> ret; 
    //insert author in the map list (it will only do it if the author didn't exist before)
    std::vector<Paper> vect;
    vect.push_back(edge.paper);
    ret = users2articles.insert( std::pair<std::string, std::vector<Paper> > (edge.author.name, vect));
    //if it already is in the map keys (the author was seen before)
    if (ret.second == false){
        //if the article is not already in the vector of articles of that author
        for (int k = 0; k < users2articles[edge.author.name].size(); k++){
            if (users2articles[edge.author.name][k].id == edge.paper.id){
                users2articles[edge.author.name].push_back(edge.paper);
            }
        }
    }
    
    //if the article was never seen before, we add it to our article2int map
    std::pair <std::unordered_map<std::string, int>::iterator, bool> ret2;
    ret2 = article2int.insert( std::pair<std::string, int> (edge.paper.id, counter));
    if (ret.second == true){
        counter += 1;
    }
}
