#pragma once
#include<string>

using namespace std;

class Matrix {
public:
	string root_directory;
	Matrix(string dir);
	int read(long i, long j);
	void write(long i, long j);
};