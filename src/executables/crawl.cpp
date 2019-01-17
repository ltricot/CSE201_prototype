#include <iostream>

#include "crawler.hpp"
#include "driver.hpp"


int main(int argc, char *argv[]) {
    curl_global_init(CURL_GLOBAL_ALL);

    //Driver d(argv[1]);
    // if we create it here we cant access it it crawl

    std::string cdata = std::string(argv[1]);
    std::string refdata = std::string(argv[2]);
    Paper source = Paper(std::string(argv[3])) ; 

    Crawler crawler = Crawler(cdata, refdata, source);
    //for(Crawler::iterator edgeit = crawler.begin(); /* nah */; ++edgeit) {
    //    Edge edge = *edgeit;
    //    d.writeEdge(edge);
    //    std::cout << edge.author.name << ", " << edge.paper.id << std::endl;
    //}

    crawler.run();
    curl_global_cleanup();
}
