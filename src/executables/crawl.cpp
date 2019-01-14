#include <iostream>

#include "crawler.hpp"
#include "driver.hpp"


int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cout << "Usage: crawl source folder" << std::endl;
        std::cout << "Example: crawl 1312.4933v2 ./interactions" << std::endl;
        return 1;
    }

    //std::cout << "hi" << std::endl;

    Driver d(argv[2]);

    //std::cout << "not abdel's driver" << std::endl;

    Crawler crawler = Crawler(Paper(std::string(argv[1])));

    //std::cout << "not the crawler" << std::endl;

    for(Crawler::iterator edgeit = crawler.begin(); /* nah */; ++edgeit) {
        //std::cout << "not the iterator" << std::endl;

        Edge edge = *edgeit;

        //std::cout << "still not the iterator" << std::endl;

        d.writeEdge(edge);

        std::cout << "wat" << std::endl;
    }
}
