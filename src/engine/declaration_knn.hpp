#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>

#include "primitives.hpp"


class Person
{
public:
    Author author;
    Person(Author author) : author(author) {}

    std::string getRecommendation(int& k) ;
    std::vector<std::string> get_k_NeighborsInteractions(int& k) ;
    std::pair<std::vector<float>,std::vector<std::string>>  getRatings_of_papers(std::vector<std::string>& list_of_papers);
    std::string get_a_Title_paper(std::pair<std::vector<float>,std::vector<std::string>>& result)

    void setPaperasRead(std::string& paper); /*update the database when we recommend a paper: create an interaction between the paper and the client*/
    

};