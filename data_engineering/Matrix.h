#pragma once
#include<string>

using namespace std;

class Matrix {
/*Adjacency matrix stored in a file system. Every row is stored in a .txt files and contains the entries where it is 1. */
public:
	string root_directory;
	Matrix();
	Matrix(string dir);
	int read(string i, string j); /* Returns the i,j'th entry of the Matrix*/
	int read(long long i, long long j);
	void write(long i, long j, int val); /*Sets the i,j'th entry to val */
	void write(string i, string j, int val);
};
