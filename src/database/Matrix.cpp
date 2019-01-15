#include "Matrix.h"
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Matrix::Matrix(string dir) {
	this->root_directory = dir;
    int res = _mkdir(dir.c_str());// , 0666);
}

Matrix::Matrix() {
	this->root_directory = "Matrix";
    int res = _mkdir("Matrix");//, 0666);
}

double Matrix::read(string i, string j) {
	string &id = i;
	string &column = j;
	while (id.length() < 11) {
		id.insert(0, 1, '0');
	}
	string id1 = this->root_directory + "/" + id.substr(0, 3);
	string id2 = id1 + "/" + id.substr(3, 3);
	string id3 = id2 + "/" + id.substr(6, 3);
	string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
	Reader r(filepath, ",");
	std::vector<std::vector<std::string>> vector = r.read();
	vector.erase(vector.begin());
	std::vector<std::vector<std::string>>::iterator it;
	for (it = vector.begin(); it != vector.end(); it++) {
		if ((*it)[0] == column) {
			return stod((*it)[1]);
		}
	}
	return 0;
}
double Matrix::read(long long i, long long j) {
	string id = to_string(i);
	string column = to_string(j);
	return this->read(id, column);
}
void Matrix::write(string i, string j, double val, string name) {
	string &id = i;
	string &column = j;
	string app = column + "," + to_string(val);
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
	ifstream inp(filepath);
	ofstream out(id3 + "/" + "tmp.txt");

	out << name << "\n";

	string line;
	bool replaced = false;
	int counter = 0;
	while (getline(inp, line)) {
		if (counter != 0) {
			vector<string> vec;
			boost::algorithm::split(vec, line, boost::is_any_of(","));
			if (vec[0] == column) {
				out << app << "\n";
				replaced = true;
			}
			else {
				out << line << "\n";
			}
		}
		counter += 1;
	}
	inp.close();

	if (replaced) {
		out.close();
		remove(filepath.c_str());
		rename((id3 + "/" + "tmp.txt").c_str(), filepath.c_str());
		return;
	}
	out << app << "\n";
	out.close();
	remove(filepath.c_str());
	rename((id3 + "/" + "tmp.txt").c_str(), filepath.c_str());
	return;
}

void Matrix::write(long i, long j, double val) {

	string id = to_string(i);
	string column = to_string(j);
	this->write(id, column, val);
}

vector<vector<string>> Matrix::getrow(string i) {
	string &id = i;
	while (id.length() < 11) {
		id.insert(0, 1, '0');
	}
	string id1 = this->root_directory + "/" + id.substr(0, 3);
	string id2 = id1 + "/" + id.substr(3, 3);
	string id3 = id2 + "/" + id.substr(6, 3);

	const char * path1 = id1.c_str();
	const char * path2 = id2.c_str();
	const char * path3 = id3.c_str();


	const int dir_er1 = _mkdir(path1); //, 0666);
    const int dir_er2 = _mkdir(path2); //, 0666);
    const int dir_er3 = _mkdir(path3); //, 0666);

	string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
	Reader r(filepath);
	vector<vector<string>> v = r.read();
	return v;
}

void Matrix::del (string i, string j) {
	string &id = i;
	string &column = j;
	while (id.length() < 11) {
		id.insert(0, 1, '0');
	}

	string id1 = this->root_directory + "/" + id.substr(0, 3);
	string id2 = id1 + "/" + id.substr(3, 3);
	string id3 = id2 + "/" + id.substr(6, 3);

	const char * path1 = id1.c_str();
	const char * path2 = id2.c_str();
	const char * path3 = id3.c_str();


	const int dir_er1 = _mkdir(path1); //, 0666);
    const int dir_er2 = _mkdir(path2); //, 0666);
    const int dir_er3 = _mkdir(path3); //, 0666);

	string filepath = id3 + "/" + id.substr(9, 2) + ".txt";
	ifstream inp(filepath);
	ofstream out(id3 + "/" + "tmp.txt");


	string line;
	while (getline(inp, line)) {
			vector<string> vec;
			boost::algorithm::split(vec, line, boost::is_any_of(","));
			if (vec[0] == column) {
				
			}
			else {
				out << line << "\n";
			}
	}
	inp.close();

	out.close();
	remove(filepath.c_str());
	rename((id3 + "/" + "tmp.txt").c_str(), filepath.c_str());
	return;
}