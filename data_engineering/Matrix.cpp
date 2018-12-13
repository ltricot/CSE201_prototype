#include "Matrix.h"
#include <string>
#include "Reader.h"
#include <fstream>

using namespace std;

Matrix::Matrix(string dir) {
	this->root_directory = dir;
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
	std::vector<std::string> vector = r.read()[0];
	if (find(vector.begin(), vector.end(), column) != vector.end()) {
		return 1;
	}
	else {
		return 0;
	}
}

void Matrix::write(long i, long j) {
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
	std::vector<std::string> vector = r.read()[0];
	if (find(vector.begin(), vector.end(), column) != vector.end()) {
		return;
	}
	else {
		ofstream output;
		output.open(filepath, ios_base::app);
		output << column + ",";
		output.close();
		return;
	}
}