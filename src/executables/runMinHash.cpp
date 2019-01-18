#include <iostream>
#include <tuple>
#include "MinHash.hpp"
#include "driver.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[]){

    std::string cdata = std::string(argv[1]);  // name of the driver
                    // filled by the crawler, from which we read
    std::string mdata = std::string(argv[2]); // name of the driver
                    // we must create then fill using min hash 
    int s = atoi(argv[3]) ; // "seuil" below which we consider that 
                    // two authors arent "friends"

    // now we get all the authors in the edges of cdata (stored in .txt)

    std::vector<Author> authors ; 
    std::vector<Edge> edges ; 

    for(auto &p : fs::recursive_directory_iterator(cdata)) {  //not sure about name of directory
        if(fs::path(p).extension() == ".txt"){
            // then we read the first line of the textfile to get the author's name
            ifstream infile(p) ;
            if(infile.good()){
                std::string author ; 
                getline(infile, author);
                Author au(author); 
                authors.push_back(au); 
            // we also take this opportunity of iterating over the authors to construct the edges
            edges.push_back(cdata.getFrom(au)) // its cdata right?
            }
        }
    }

    // now we feed minhash with the edges we have collected
    MinHash minhash(30) ;
    for(std::vector<Edge>::iterator ite = edges.begin() ; ite != edges.end() ; ite++){
        minhash.update(ite) ;  
    }

    // now we construct and fill the driver mdata 
    Driver mdada(mdata) ; 

    for(std::vector<Author>::iterator au1 = authors.begin() ; au1 != authors.end() ; au1++){
        for(std::vector<Author>::iterator au2 = authors.begin() ; au2 != authors.end() ; au2++){
            float sim = minhash.getSimilarity(au1,au2);
            if(sim > s){  // we take the "friendship" into account
                mdata.writeEdge(std::make_tuple(au1,au2,sim)) ; 
            }
        }
    }
}
