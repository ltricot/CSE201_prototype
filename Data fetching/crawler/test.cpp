#include "crawlerc.hpp"
#include <iostream>


int main(int argc, char** argv) {
    std::vector<std::pair<std::string, std::string>>::iterator pair;
    Crawler *crawler = new Crawler();
    crawler->crawl("1812.01161", 6);

    for(pair = crawler->pairs.begin(); pair != crawler->pairs.end(); pair++) {
        std::cout << pair->first << ", " << pair->second << std::endl;
    }
}
