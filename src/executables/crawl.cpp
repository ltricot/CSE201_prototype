#include <iostream>

#include "crawler.hpp"
#include "driver.hpp"


int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cout << "Usage: crawl source folder" << std::endl;
        std::cout << "Example: crawl 1312.4933v2 ./interactions" << std::endl;
        return 1;
    }

    Driver d(argv[2]);

    Crawler crawler = Crawler(Paper(std::string(argv[1])));
    for(auto edge : crawler) {
        d.writeEdge(edge);
        // also do : TBD by Loan
    }
}
