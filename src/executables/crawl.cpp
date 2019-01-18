#include <iostream>

#include "crawler.hpp"
#include "driver.hpp"


int main(int argc, char *argv[]) {
    curl_global_init(CURL_GLOBAL_ALL);

    std::string cdata = std::string(argv[1]);
    std::string refdata = std::string(argv[2]);
    std::string sdata = std::string(argv[3]);  
    Paper source = Paper(std::string(argv[4])) ; 


    Crawler crawler = Crawler(cdata, refdata, sdata, source);
    //for(Crawler::iterator edgeit = crawler.begin(); /* nah */; ++edgeit) {
    //    Edge edge = *edgeit;
    //    d.writeEdge(edge);
    //    std::cout << edge.author.name << ", " << edge.paper.id << std::endl;
    //}

    crawler.run();
    curl_global_cleanup();
}
