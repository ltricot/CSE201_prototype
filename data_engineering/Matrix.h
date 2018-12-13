#pragma once
#include<string>

using namespace std;

class Matrix {
/*Adjacency matrix stored in a file system. Every row is stored in a .txt files and contains the entries where it is 1. */
public:
	string root_directory;
	Matrix(string dir);
	int read(long i, long j); /* Returns the i,j'th entry of the Matrix*/
	void write(long i, long j); /*Sets the i,j'th entry to 1 */
};
