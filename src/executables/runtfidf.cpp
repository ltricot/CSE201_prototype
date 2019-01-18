#include <iostream>
#include "tfidfinterface.hpp"
#include "driver.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[]){
    std::string sdata = std::string(argv[1]);  // name of the driver
                    // filled by minhash, from which we read

    std::string tfidfdata = std::string(argv[2]); // name of the driver
                    // we must create then fill using tfidf

    Driver dtfidf(tfidfdata);

    TFIDF tfidf(sdata);
    for(TFIDF::iterator ite = tfidf.begin(); ite != tfidf.end() ; ite++){
        TFIDF::pEdge edge = *ite ;
        Author word = Author(std::get<0>(edge));    // sorry for this abomination
        Paper paper = std::get<1>(edge);
        double weight = std::get<2>(edge);
        Edge newEdge(word,paper,edge);

        dtfidf.writeEdge(newEdge);
    }
}




