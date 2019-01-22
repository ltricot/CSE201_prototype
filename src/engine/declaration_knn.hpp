#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>
#include "driver.hpp"
#include "primitives.hpp"


class Person {
    private:
    
    std::string outfolder;
    std::string cdata;
    std::string vdata;
    Author author;
    std::map<std::string, int> keys;
    
    public:
    
    Person(Author author, std::string cdata, std::string cldata, std::string vdata);

    std::vector<Author> cluster; // $$

    std::string getRecommendation(int k) ;

    std::vector<std::string> get_k_NeighborsInteractions(int &k) ;

    std::pair<std::vector<double>,std::vector<std::string>>  getRatings_of_papers(std::vector<std::string> &list_of_papers);

    std::string get_a_title_paper(std::pair<std::vector<double>,std::vector<std::string>> result);

    void setPaperasRead(std::string &paper); /*update the database when we recommend a paper: create an interaction between the paper and the client, need to be done*/
};


std::map<std::string, int> getAuthorClusters(std::string cldata);
