#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include <Eigen/Eigen>


using namespace std;


class Vectors {
    public:
    string root_directory;
    Vectors(string dir) : root_directory(dir) {}

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

        const int dir_er1 = mkdir(path1, 0666);
        const int dir_er2 = mkdir(path2, 0666);
        const int dir_er3 = mkdir(path3, 0666);
        	
        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
        
        ofstream out(filepath);

        for(int i = 0; i < size; i++){
            out << vec[0, i] << "\n";
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

        const int dir_er1 = mkdir(path1, 0666);
        const int dir_er2 = mkdir(path2, 0666);
        const int dir_er3 = mkdir(path3, 0666);

        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";

        ifstream inp(filepath);
        int counter = 0;
        Eigen::Matrix<double, size, 1> ret;
	    string line;
        while (getline(inp, line)) {
            ret(0, counter) = line;
            counter += 1;
        }

        return ret;
    }
};
