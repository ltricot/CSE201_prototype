#include "driver.hpp"
#include "Matrix.h"
#include <stdio.h>
#include<vector>
#include<string>
#include <unordered_map>
#include <sstream>
#include<iostream>
#include <experimental/filesystem>
#include "Summaries.h"

namespace fs = std::experimental::filesystem;
using namespace std;


const int lat_feat = 30;


template <class KeyT> std::vector<KeyT> Driver::getKeys() {
	std::vector<KeyT> keys;
	
	Reader r(this->keysfile);
	vector<vector<string>> tmp = r.read();

	for (vector<vector<string>>::iterator it = tmp.begin(); it != tmp.end(); it++){
		string foo = (*it)[0];
		KeyT baa(foo);
		keys.push_back(baa);
	}

	return keys;
	/*for(auto &p : fs::recursive_directory_iterator(directory)) {
        if(p.path().extension() == ".txt") {
            // then we read the first line of the textfile to get the key
            ifstream infile(p.path()) ;

            if(infile.good()){
                std::string keystr ; 
                getline(infile, keystr);
				KeyT key(keystr) ; 
                key.push_back(key); 
            }
        }
	}*/
}

Driver::Driver(string dir){ 
	this->directory = dir;
	this->keysfile = dir + "/keys.txt";
    int res = mkdir(dir.c_str(), 0666);
}

bool Driver::writeEdge(Edge edge) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = edge.author.name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = edge.paper.id;
	m.write(row, col, edge.weight, n);
	ofstream keys(this->keysfile);
	keys << n << "\n";
	return true; 
}

bool Driver::writeEdge(Reference ref) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = ref.first.id;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = ref.second.id;
	m.write(row, col, 1, n);
	ofstream keys(this->keysfile);
	keys << n << "\n";
	return true;
}

bool Driver::writeEdge(Friends friends) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = get<0>(friends).name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = get<1>(friends).name;
	m.write(row, col, get<2>(friends), n);
	ofstream keys(this->keysfile);
	keys << n << "\n";
	return true;
}

bool Driver::removeEdge(Edge edge) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = edge.author.name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;	
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = edge.paper.id;
	m.del(row, col);
	return true;
}

bool Driver::removeEdge(Reference ref) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = ref.first.id;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;	
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = ref.second.id;
	m.del(row, col);
	return true;
}

bool Driver::removeEdge(Friends friends){
	hash<string> hasher;
	Matrix m(this->directory);
	string n = get<0>(friends).name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;	
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = get<1>(friends).name;
	m.del(row, col);
	return true;
}


vector<Edge> Driver::getFrom(Author from) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = from.name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	vector<vector<string>> res = m.getrow(row);
	vector<Edge> ret;

	if(res.size() == 0)
		return ret;
	res.erase(res.begin());

	for (vector<vector<string>>::iterator it = res.begin(); it < res.end(); it++) {
		vector<string> line = *it  ;
		Edge edge;
		edge.readVector(line, n);
		ret.push_back(edge);
	}

	return ret;
}

vector<Friends> Driver::getFrom(Author from, bool fr) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = from.name;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	vector<vector<string>> res = m.getrow(row);
	vector<Friends> ret;

	if(res.size() == 0)
		return ret;
	res.erase(res.begin());

	for (vector<vector<string>>::iterator it = res.begin(); it < res.end(); it++) {
		vector<string> line = *it  ;
		Friends edge = std::make_tuple(from, Author(line[0]), stod(line[1]));
		ret.push_back(edge);
	}

	return ret;
}


vector<Reference> Driver::getFrom(Paper from) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = from.id;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	vector<vector<string>> res = m.getrow(row);
	vector<Reference> ret;

	if(res.size() == 0)
		return ret;
	res.erase(res.begin());

	for (vector<vector<string>>::iterator it = res.begin(); it < res.end(); it++) {
		vector<string> line = *it  ;
		Reference ref;
		ref.first = from;
		ref.second = line[0];
		ret.push_back(ref);
	}

	return ret;
}


bool Driver::writeEdges(vector<Edge> edges) {
	for (vector<Edge>::iterator it = edges.begin(); it < edges.end(); it++) {
		this->writeEdge(*it);
	}
	return true;
}

bool Driver::writeEdges(vector<Reference> ref){
	for (vector<Reference>::iterator it = ref.begin(); it < ref.end(); it++) {
		this->writeEdge(*it);
	}
	return true;	
}

bool Driver::writeEdges(vector<Friends> friends){
	for (vector<Friends>::iterator it = friends.begin(); it < friends.end(); it++) {
		this->writeEdge(*it);
	}
	return true;
}

bool Driver::removeEdges(vector<Edge> edges){
	for (vector<Edge>::iterator it = edges.begin(); it < edges.end(); it++) {
		this->removeEdge(*it);
	}
	return true;
}

bool Driver::removeEdges(std::vector<Reference> refs){
	for (vector<Reference>::iterator it = refs.begin(); it < refs.end(); it++) {
		this->removeEdge(*it);
	}
	return true;	
}

bool Driver::removeEdges(std::vector<Friends> friends) {
	for (vector<Friends>::iterator it = friends.begin(); it < friends.end(); it++) {
		this->removeEdge(*it);
	}

	return true;	
}

vector<Edge> Driver::getFroms(vector<Author> froms) {
	vector<Edge> ret;
	for (vector<Author>::iterator it = froms.begin(); it < froms.end(); it++) {
		vector<Edge> tmp =  this->getFrom(*it);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}


SummaryAccessor::SummaryAccessor(string dir){
	this->directory = dir;
	this->keysfile = dir + "/keys.txt";
	int res = mkdir(dir.c_str(), 0666);
}

void SummaryAccessor::sendSummary(Paper paper, string summary){
	hash<string> hasher;
	string n = paper.id;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string id = ostr.str();
	Summaries s(this->directory);
	ofstream keys(this->keysfile);
	keys << n << "\n";
	s.storeSummary(id, summary);
}

string SummaryAccessor::getSummary(Paper paper){
	hash<string> hasher;
	string n = paper.id;
	size_t foo = hasher(n);
	foo = foo % 100000000000LU;
	std::ostringstream ostr;
	ostr << foo;
	string id = ostr.str();
	Summaries s(this->directory);
	return s.getSummary(id);
}

std::vector<Paper> SummaryAccessor::getKeys() {
	std::vector<Paper> keys;
	
	Reader r(this->keysfile);
	vector<vector<string>> tmp = r.read();

	for (vector<vector<string>>::iterator it = tmp.begin(); it != tmp.end(); it++){
		string foo = (*it)[0];
		Paper baa(foo);
		keys.push_back(baa);
	}

	return keys;
}