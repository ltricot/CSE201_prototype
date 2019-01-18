#include <experimental/filesystem>
#include <string>
#include <fstream>
#include "driver.hpp"
#include "clusteringlast.hpp"

namespace fs = std::experimental::filesystem;
using namespace std;


int main(int argc, char *argv[]) {
    string mdata = argv[1];
    Driver driver(mdata);

    vector<Friends> similarities;
    vector<Author> authors=driver.getKeys<Author>();
    for (vector<Author>::iterator it=authors.begin();it!=authors.end();it++){
        std::vector<Friends> tmp=(dcdata.getFrom(*it,fr=true));
        similarities.insert(similaries.end(), tmp.begin(), tmp.end());
    }

    Cluster clustering(similarities);
    unordered_map<int,std::vector<Author>> clusters=clustering.clusters;
    string outfolder = argv[2];

    for (unordered_map<int,vector<Author>>::iterator it=clusters.begin();it!=clusters.end();it++){
        string label= std::to_string(it->first);
        string path=outfolder+"/"+label+".txt";
        ofstream myfile(path);
        if myfile.is_open{
            for (vector<Author>::iterator i=it->second.begin();i!=it->second.end();i++){
                myfile<<Author.name
                myfile<<"\n"
            }
            myfile.close()
        }
    }
}
