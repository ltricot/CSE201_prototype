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

    std::string getRecommendation(int& k) const;
    std::vector<std::string> get_k_NeighborsInteractions(int& k) const;
    std::pair<std::vector<int>,std::vector<std::string>>  getRatings_of_papers(std::vector<std::string>& list_of_papers);
    std::string get_a_Title_paper(std::pair<std::vector<int>,std::vector<std::string>>& result)

    void setPaperasRead(std::string& paper); /*a voir si pas deja fait autre part*/
    

};