#include "driver.hpp"
#include "Matrix.h"
#include<vector>
#include<string>
#include <unordered_map>
#include <sstream>
#include<iostream>

using namespace std;


const int lat_feat = 30;

Driver::Driver(string dir){ 
	this->directory = dir;
    int res = mkdir(dir.c_str(), 0666);
}
bool Driver::writeEdge(Edge edge) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = edge.author.name;
	size_t foo = hasher(n);
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = edge.paper.id;
        
	Eigen::Matrix<double, lat_feat, 1> p = (Eigen::MatrixXd::Random(lat_feat, 1) + Eigen::MatrixXd::Constant(lat_feat,1, 1.))*0.5;
    Eigen::Matrix<double, lat_feat, 1> q =
        (Eigen::MatrixXd::Random(lat_feat, 1) + Eigen::MatrixXd::Constant(lat_feat, 1, 1.)) *
            0.5;
    VectorAccessor<lat_feat> v("MatFact");
	Eigen::Matrix<double, lat_feat, 1> vect1 = v.get_vector(edge.author);
    if (vect1(1, 0) == -DBL_MAX) {
		v.send_vector(edge.author, p);
		}        
    if (v.get_vector(edge.paper)(1,0) == -DBL_MAX){
		v.send_vector(edge.paper, q);
	}
	
	m.write(row, col, edge.weight, n);
	return true;
}

bool Driver::removeEdge(Edge edge) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = edge.author.name;
	size_t foo = hasher(n);
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	string col = edge.paper.id;
	m.del(row, col);
	return true;
}

vector<Edge> Driver::getFrom(Author from) {
	hash<string> hasher;
	Matrix m(this->directory);
	string n = from.name;
	size_t foo = hasher(n);
	std::ostringstream ostr;
	ostr << foo;
	string row = ostr.str();
	vector<vector<string>> res = m.getrow(row);
	vector<Edge> ret;
	res.erase(res.begin());

	for (vector<vector<string>>::iterator it = res.begin(); it < res.end(); it++) {
		vector<string> line = *it  ;
		Edge edge;
		edge.readVector(line, n);
		ret.push_back(edge);
	}

	return ret;
}

bool Driver::writeEdges(vector<Edge> edges) {
	for (vector<Edge>::iterator it = edges.begin(); it < edges.end(); it++) {
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

vector<Edge> Driver::getFroms(vector<Author> froms) {
	vector<Edge> ret;
	for (vector<Author>::iterator it = froms.begin(); it < froms.end(); it++) {
		vector<Edge> tmp =  this->getFrom(*it);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}
