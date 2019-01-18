#include <experimental/filesystem>
#include <string>
#include <fstream>
#include "driver.hpp"
#include "clusteringlast.hpp"

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
    map<int,std::vector<std::string>> clusters=clustering.clusters;

    for (map<int,vector<string>>::iterator it=clusters.begin(); it!=clusters.end(); ++it) {
        string label= std::to_string(it->first);
        string path=outfolder + "/" + label + ".txt";
        string keyfile = outfolder + "/" + "keys.txt";

        ofstream keys(keyfile, std::ios_base::app);
        keys << label << "\n";
        keys.close();

        ofstream myfile(path);
        for (vector<string>::iterator i=it->second.begin();i!=it->second.end();i++)
            myfile << i << '\n';

        myfile.close();
    }
}
