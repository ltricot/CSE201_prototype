#include <iostream>

#include "crawler.hpp"
#include "driver.hpp"


int main(int argc, char *argv[]) {
    curl_global_init(CURL_GLOBAL_ALL);

    if(argc != 3) {
        std::cout << "Usage: crawl source folder" << std::endl;
        std::cout << "Example: crawl 1312.4933v2 ./interactions" << std::endl;
        return 1;
    }

    Driver d(argv[2]);
    Crawler crawler = Crawler(Paper(std::string(argv[1])));
    for(Crawler::iterator edgeit = crawler.begin(); /* nah */; ++edgeit) {
        Edge edge = *edgeit;
        d.writeEdge(edge);

        std::cout << edge.author.name << ", " << edge.paper.id << std::endl;
    }

    curl_global_cleanup();
}
