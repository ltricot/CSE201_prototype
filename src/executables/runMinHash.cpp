#include "MinHash.hpp"
#include "driver.hpp"
#include <iostream>
#include <tuple>
#include <set>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

int main(int argc, char *argv[]) {

    std::string cdata = std::string(argv[1]); // name of the driver
                                              // filled by the crawler, from which we read
    Driver dcdata(cdata);

    std::string mdata = std::string(argv[2]); // name of the driver
                                              // we must create then fill using min hash
    double s = stod(argv[3]);                 // "seuil" below which we consider that
                                              // two authors arent "friends"

    // now we get all the authors in the edges of cdata (stored in .txt)
    std::vector<Edge> edges;

    std::vector<Author> authors = dcdata.getKeys<Author>();
    std::set<std::string> seen;
    for(auto au : authors)
        seen.insert(au.name);
    
    authors.clear();

    for (auto au : seen) {
        std::vector<Edge> temp = (dcdata.getFrom(Author(au)));
        edges.insert(edges.end(), temp.begin(), temp.end());
    }

#ifdef replacedBygetKeys
    for (auto &p : fs::recursive_directory_iterator(cdata)) { // not sure about name of directory
        if (p.path().extension() == ".txt") {
            // then we read the first line of the textfile to get the author's name
            ifstream infile(p.path());

            if (infile.good()) {
                std::string author;
                getline(infile, author);
                Author au(author);
                authors.push_back(au);
                // we also take this opportunity of iterating over the authors to construct the
                // edges
                std::vector<Edge> temp = (dcdata.getFrom(au)); // its cdata right?
                edges.insert(edges.end(), temp.begin(), temp.end());
            }
        }
    }
#endif

    // now we feed minhash with the edges we have collected
    MinHash minhash(30);
    for (std::vector<Edge>::iterator ite = edges.begin(); ite != edges.end(); ite++) {
        minhash.update(*ite);
    }

    // now we construct and fill the driver mdata
    Driver dmdata(mdata);
    for (auto au1_s : seen) {
        Author au1 = Author(au1_s);

        for (auto au2_s : seen) {
            Author au2 = Author(au2_s);
            double sim = (double)minhash.getSimilarity(au1, au2);
            if (sim > s) { // we take the "friendship" into account
                dmdata.writeEdge(std::make_tuple(au1, au2, sim));
            }
        }
    }
}
