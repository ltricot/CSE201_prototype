//Author: Jules BAUDET
#include <iostream>
#include <vector>
#include <map>
#include <string> 

#include "MinHash.hpp"
#include <random>
#include <algorithm>

int randint(int min, int max) {
    // function that generates a random integer between 0 and 1500000
    std::random_device rd;     // used once to initialise engine
    std::mt19937 rng(rd());    // random-number engine
    std::uniform_int_distribution<int> uni(min,max);

    int random_integer = uni(rng);
    return random_integer;
}

void printPair(const std::pair<std::string, std::vector<std::string> > &p)
{
    std::cout << "Key: " << p.first << std::endl;
    copy(p.second.begin(), p.second.end(), std::ostream_iterator<std::string>(std::cout, ""));
}

void test(){
    //a test function that creates a data set and uses MinHash on it
    MinHash test_class = MinHash(150);
    int author_nb = 100;
    int paper_nb = 8;
    int max_paper_by_author = 3; //the maximum number of papers an author can cite
    //we create some random edges
    //for each author
    for (int i = 0; i < author_nb; i++){
        Author author = Author(std::to_string(i)); //give a name to my author 
        int nb = randint(1, max_paper_by_author); //number of papers my author will cite
        for (int j=0; j < nb; j++){
            Paper paper (std::to_string(randint(1, paper_nb))); //random paper whose title is an integer
            Edge edge(author, paper);
            test_class.update(edge); //add the edge to our MinHash class
        }
    }
    test_class.getInfo();
    //we now compute a few similarities
    int simi = test_class.getSimilarity(Author("1"), Author("2"));
    std::cout<< simi <<std::endl;
    simi = test_class.getSimilarity(Author("1"), Author("3"));
    std::cout<< simi <<std::endl;
    simi = test_class.getSimilarity(Author("1"), Author("4"));
    std::cout<< simi <<std::endl;
    simi = test_class.getSimilarity(Author("1"), Author("5"));
    std::cout<< simi <<std::endl;
    simi = test_class.getSimilarity(Author("1"), Author("6"));
    std::cout<< simi <<std::endl; 

    for_each(test_class.users2articles.begin(), test_class.users2articles.end(), printPair);
}

int main(){
    test();
    std::cout<<"YOU PASSED ALL THE TESTS, LVL: CODE GOD"<<std::endl;
    return 0;
}
