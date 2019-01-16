#pragma once
#include "Matrix.h"
#include "Reader.h"
#include "driver.hpp"

class ReferencesReader : public Reader {
	/* Specialized reader which reads a file containing the edges of a graph, then creates and stores the adjacency matrix of that graph */
public:
	std::string filename;
	ReferencesReader(std::string name);
	Matrix MakeMatrix(); /*Read the file and makes the matrix  */
    vector<Edge> GetEdges();
};
