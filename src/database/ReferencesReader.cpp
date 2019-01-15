#include "ReferencesReader.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>

using namespace std;

ReferencesReader::ReferencesReader(string name) {
	this->filename = name;
	this->delim = "\t";
}

Matrix ReferencesReader::MakeMatrix() {
	/*First attempt at storing a Matrix. The idea is to construct a directory in the form of a tree structure.
	Every row is stored in a file row.txt. The path to the file is obtained by first padding
	the row number with zeroes on the left, cutting it up into  substrings of length three, then appending them,
	for example, to store the 00123184945'th row, we would create the file 001/231/849/45.txt */
	Matrix m;

	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		vector<string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(this->delim));
		string id = vec[0];
		string ref = vec[1];
		Driver d;
		d.writeEdge(Edge(Author(id), Paper(ref), 1));
	}
	file.close();
	return m;
}

vector<Edge> ReferencesReader::GetEdges() {
    /*First attempt at storing a Matrix. The idea is to construct a directory in the form of a tree
    structure. Every row is stored in a file row.txt. The path to the file is obtained by first
    padding the row number with zeroes on the left, cutting it up into  substrings of length three,
    then appending them, for example, to store the 00123184945'th row, we would create the file
    001/231/849/45.txt */
    Matrix m;

    ifstream file(filename);
    string line;
    vector<Edge> ret;
    while (getline(file, line)) {
        vector<string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(this->delim));
        string id = vec[0];
        string ref = vec[1];
        Driver d;
        ret.push_back(Edge(Author(id), Paper(ref), 1));
    }
    file.close();
    return ret;
}


