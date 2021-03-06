#include "clusteringlast.hpp"
#include "driver.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <string>

namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char *argv[]) {
    string mdata = argv[1];
    string outfolder = argv[2];
    Driver dmdata(mdata);

    vector<Friends> similarities;
    vector<Author> authors = dmdata.getKeys<Author>();
    for (vector<Author>::iterator it = authors.begin(); it != authors.end(); it++) {
        std::vector<Friends> tmp = (dmdata.getFrom(*it, true));
        similarities.insert(similarities.end(), tmp.begin(), tmp.end());
    }

    Cluster clustering(similarities);
    map<int, std::vector<std::string>> clusters = clustering.clusters;

    for (map<int, vector<string>>::iterator it = clusters.begin(); it != clusters.end(); ++it) {
        // string label = std::to_string(it->first);

        std::vector<Author> authors;
        for (auto au_s : it->second)
            authors.push_back(Author(au_s));
        
        if(fs::exists(outfolder))
            fs::create_directory(outfolder);

        // addKey(outfolder, it->first);
        setNeighbors(outfolder, it->first, authors);

        #ifdef outdated
        string path = outfolder + "/" + label + ".txt";
        ofstream myfile(path);

        for (vector<string>::iterator i = it->second.begin(); i != it->second.end(); i++)
            myfile << *i << '\n';

        myfile.close();
        #endif
    }
}
