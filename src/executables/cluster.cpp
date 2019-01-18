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
    for(auto &p : fs::recursive_directory_iterator(cdata)) {  //not sure about name of directory
        if(p.path().extension() == ".txt") {
            // then we read the first line of the textfile to get the author's name
            ifstream infile(p.path()) ;

            if(infile.good()){
                std::string author ; 
                getline(infile, author);
                Author au1(author); 
            std::vector<Friends> temp = (dcdata.getFrom(au)); 
            similarities.insert(similaries.end(), temp.begin(), temp.end());
            }
        }
    }

    Cluster clustering(similarities);
    map<int,std::vector<Author>> clusters=clustering.clusters;
    string outfolder = argv[2];

    for (map<int,vector<Author>>::iterator it=clusters.begin();it!=clusters.end();it++){
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
