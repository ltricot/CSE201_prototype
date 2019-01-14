#include <iostream>
#include "crawler.hpp"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Provide exactly one source paper ID" << std::endl;
        return 1;
    }

    Driver d ; 

    Crawler crawler = Crawler(Paper(std::string(argv[1])));
    for(Crawler::iterator edgeit = crawler.begin() ; edgeit != crawler.end() ; edgeit++){
        d.writeEdge(*edgeit) ;
        // also do : TBD by Loan
    }
}
