#include "crawlerc.hpp"
#include <iostream>


int main(int argc, char** argv) {
    Crawler *crawler = new Crawler();
    std::vector<std::pair<std::string, std::string>> pairs;
    std::vector<std::string> authors;
    authors.push_back("Kortchemski");

    pairs = crawler->fromAuthors(authors);
    std::vector<std::pair<std::string, std::string>>::iterator pair;
    std::cout << pairs.size() << std::endl;

    for(pair = pairs.begin(); pair != pairs.end(); pair++) {
        std::cout << pair->first << std::endl;
    }
}
