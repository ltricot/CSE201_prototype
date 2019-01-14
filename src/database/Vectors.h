#pragma once
#include <string>
#include <vector>
#include "C:\Users\Abdel\Downloads\eigen-eigen-323c052e1731\eigen-eigen-323c052e1731\Eigen"

using namespace std;
class Vectors{
    public:
    string root_directory;
    UserVectors();
    UserVectors(string dir);
    template <int size> void storevector(string id, Matrix<double, size, 1> vec){
	    while (id.length() < 11) {
		    id.insert(0, 1, '0');
	    }
        string id1 = this->root_directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char * path1 = id1.c_str();
        const char * path2 = id2.c_str();
        const char * path3 = id3.c_str();

        const int dir_er1 = _mkdir(path1);
        const int dir_er2 = _mkdir(path2);
        const int dir_er3 = _mkdir(path3);
        	
        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
        
        ofstream out(filepath);

        while(int i = 0; i < size; i++){
            out << vec[0, i] << "\n";
        }
    }
    
    template <int size> Matrix<double, size, 1> getvector(string id){
        while (id.length() < 11){
            id.insert(0, 1, '0');
        }
        string id1 = this->root_directory + "/" + id.substr(0, 3);
        string id2 = id1 + "/" + id.substr(3, 3);
        string id3 = id2 + "/" + id.substr(6, 3);

        const char * path1 = id1.c_str();
        const char * path2 = id2.c_str();
        const char * path3 = id3.c_str();

        const int dir_er1 = _mkdir(path1);
        const int dir_er2 = _mkdir(path2);
        const int dir_er3 = _mkdir(path3);

        string filepath = id3 + "/" + id.substr(9, 2) + ".txt";

        ifsteam inp(filepath);

        Matrix<double, size, 1> ret;

        int counter = 0;

	    string line;
        while (getline(inp, line)) {
            ret[0, counter] = line;
            counter += 1;
        }
        return ret;
    }  

}