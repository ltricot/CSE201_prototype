#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cfloat>
#include "Eigen/Eigen"




using namespace std;

/** @brief Special class for a collection of vectors, stored in the file system
 * 
 * @details Class implementation of a file system which acts as a way to store vectors. 
 *  Each vector is associated to either an author or a paper, with each one of those 
 * associated to a unique (well, almost unique, some conflicts may exists but hopefully not a lot) identifier. 
 * This identifier is then used to make a .txt file and place it in the tree/file system. This is the same file system
 * as the one described and used for the Matrix class
 */
class Vectors {
    public:
    string root_directory;
    Vectors(string dir);

    ///@brief Stores the vector
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
            out << vec(i, 0) << "\n";
        }
    }
    
    ///@brief Restores the vector
    template <int size> Eigen::Matrix<double, size, 1> getvector(string id){
        while (id.length() < 11){
            id.insert(0, 1, '0');
        }

		string id1 = this->root_directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char *path1 = id1.c_str();
        const char *path2 = id2.c_str();
        const char *path3 = id3.c_str();

        const int dir_er1 = mkdir(path1, 0666);
        const int dir_er2 = mkdir(path2, 0666);
        const int dir_er3 = mkdir(path3, 0666);

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
