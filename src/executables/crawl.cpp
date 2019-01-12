#include <iostream>
#include "crawler.hpp"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Provide exactly one source paper ID" << std::endl;
        return 1;
    }

    Crawler crawler = Crawler(Paper(std::string(argv[1])));
    for(auto edge : crawler) {
        std::cout << edge.paper.id << std::endl;
    }
}
