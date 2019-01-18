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
    map<int,std::vector<Author>> clusters=clustering.clusters;

    for (map<int,vector<Author>>::iterator it=clusters.begin();it!=clusters.end();it++) {
        string label= std::to_string(it->first);
        string path=outfolder+"/"+label+".txt";
        ofstream myfile(path);

        for (vector<Author>::iterator i=it->second.begin();i!=it->second.end();i++)
            myfile << i->name << '\n';

        myfile.close();
    }
}
