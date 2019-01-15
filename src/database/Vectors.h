#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cfloat>
#include "../../libraries/eigen-eigen-323c052e1731/Eigen/Eigen"


#include <direct.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;


class Vectors {
    public:
    string root_directory;
    Vectors(string dir);

    template <int size> void storevector(string id, Eigen::Matrix<double, size, 1> vec){
	    while (id.length() < 11) {
		    id.insert(0, 1, '0');
	    }

        string id1 = this->root_directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char * path1 = id1.c_str();
        const char * path2 = id2.c_str();
        const char * path3 = id3.c_str();

        const int dir_er1 = _mkdir(path1);//, 0666);
        const int dir_er2 = _mkdir(path2);//, 0666);
        const int dir_er3 = _mkdir(path3);//, 0666);
        	
        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
        
        ofstream out(filepath);

        for(int i = 0; i < size; i++){
            out << vec(i, 0) << "\n";
        }
    }
    
    template <int size> Eigen::Matrix<double, size, 1> getvector(string id){
        while (id.length() < 11){
            id.insert(0, 1, '0');
        }

        string id1 = this->root_directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char * path1 = id1.c_str();
        const char * path2 = id2.c_str();
        const char * path3 = id3.c_str();

        const int dir_er1 = _mkdir(path1);//, 0666);
        const int dir_er2 = _mkdir(path2);//, 0666);
        const int dir_er3 = _mkdir(path3);//, 0666);

        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";

        ifstream inp(filepath);
        int counter = 0;
        Eigen::Matrix<double, size, 1> ret;
        ret(1,0) = -DBL_MAX;
		string line;
        while (getline(inp, line)) {
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());
            ret(counter, 0) = stod(line);
            counter += 1;
        }
        return ret;
    }
};
