#include "Matrix.h"
#include <string>
#include "Reader.h"
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>

using namespace std;

Matrix::Matrix(string dir) {
	this->root_directory = dir;
	int res = _mkdir(dir.c_str());
}

int Matrix::read(long i, long j) {
	string id = to_string(i);
	string column = to_string(j);
	while (id.length() < 11) {
		id.insert(0, 1, '0');
	}
	string id1 = id.substr(0, 3);
	string id2 = id1 + "/" + id.substr(3, 3);
	string id3 = id2 + "/" + id.substr(6, 3);
	string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
	Reader r(filepath, ",");
	std::vector<std::vector<std::string>> vector = r.read();
	
	if (find(vector.begin(), vector.end(), column) != vector.end()) {
		return 1;
	}
	else {
		return 0;
	}
}

void Matrix::write(long i, long j, long val) {
	
	string id = to_string(i);
	string column = to_string(j);
	string app = column + "," + to_string(val);
	while (id.length() < 11) {
		id.insert(0, 1, '0');
	}
	
	string id1 = id.substr(0, 3);
	string id2 = id1 + "/" + id.substr(3, 3);
	string id3 = id2 + "/" + id.substr(6, 3);
	
	const char * path1 = id1.c_str();
	const char * path2 = id2.c_str();
	const char * path3 = id3.c_str();
	
	const int dir_er1 = _mkdir(path1);
	const int dir_er2 = _mkdir(path2);
	const int dir_er3 = _mkdir(path3);
	
	string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
	ifstream inp(filepath);
	ofstream out(id3 + "/" + "tmp.txt");
	
	string line;
	bool replaced = false
	
	while (getline(inp, line)) {
		vector<string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(","));
		if (vec[0] == column){
			out << app << "\n";
			replaced = true;
		}
		else{
			out << line << "\n";
		}
	}
	inp.close();
	
	if (replaced){
		out.close();
		remove(filepath.c_str());
		rename( (id3 + "/" + "tmp.txt").c_str() , filepath.c_str());
		return;
	}
	out<<app<<"\n";
	out.close();
	remove(filepath.c_str());
	rename( (id3 + "/" + "tmp.txt").c_str() , filepath.c_str());
	return;
	
	/*
	Reader r(filepath, ",");
	std::vector<std::vector<std::string>> mat = r.read();
	int a = mat.size();
	int b = mat[0].size(); //Should be 3
	for (int it1 = 0, it1 <a, it1++){
		
	if (find(vector.begin(), vector.end(), column) != vector.end()) {
		return;
	}
	else {
		ofstream output;
		output.open(filepath, ios_base::app);
		output << column + ",";
		output.close();
		return;
	}*/
}