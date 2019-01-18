#include "Summaries.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <algorithm>
#include "Reader.h"

using namespace std;
Summaries::Summaries(string dir){
    this->directory = dir;
    int res = mkdir(dir.c_str(), 0666);
}

void Summaries::storeSummary(string id, string summary){
        summary.erase(remove(summary.begin(), summary.end(), '\n'), summary.end());

        while (id.length() < 11){
            id.insert(0, 1, '0');
        }

		string id1 = this->directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char *path1 = id1.c_str();
        const char *path2 = id2.c_str();
        const char *path3 = id3.c_str();

        const int dir_er1 = mkdir(path1, 0666);
        const int dir_er2 = mkdir(path2, 0666);
        const int dir_er3 = mkdir(path3, 0666);

        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
        
        ofstream out(filepath);

        out << summary;
        out.close();
        return;
}

string Summaries::getSummary(string id){
     while (id.length() < 11){
            id.insert(0, 1, '0');
        }

        string id1 = this->directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3); 

        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";

        Reader r(filepath);

        return (r.read[0])[0];
}