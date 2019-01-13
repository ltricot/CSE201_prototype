#pragma once
#include<string>
#include<vector>
#include"Reader.h"
using namespace std;

class Matrix {
	/** @brief Adjacency matrix stored in a file system.
	 *
	 * @details Adjacency Matrix class. The idea is to construct a directory in the form of a tree structure.
	 *	Every row is stored in a file row.txt which contains the non-zero entries of that row. The path to the
	 *  file is obtained by first padding the row number with zeroes on the left, cutting it up into  substrings
	 *  of length three, then appending them, for example, to store the 00123184945'th row, we would create the
	 *  file 001/231/849/45.txt  Each line in the text file represents one edge and follows the following format:
	 * "column, weight" */
public:

	//Stores the root directory for the files of the matrix
	string root_directory;

	Matrix();
	Matrix(string dir);

	/** @brief Read the matrix entries
	 *
	 * @details Recovers the path to the text file for the i'th line, then looks for j in it. If it finds it returns
	 * the associated weight, if not returns 0.
	 *
	 * @param i the row as a string in case it is too big to be stored in a long
	 *
	 * @param j the column as a string in case it is too big to be stored in a long
	 *
	 *@return the value of the i,j'th entry
	 * */
	double read(string i, string j);

	/**
	 * @param i the row
	 *
	 * @param j the column
	 * */
	double read(long long i, long long j);

	/** @bried Modify the matrix
	 *
	 * @details Recovers the path to the text file of the i'th line, then looks for j in it. If it finds it,
	 * modifies the value of the weight to val, if not adds it at the end of the file with val as the weight.
	 *
	 * @param i the row as a string in case it is too big to be stored in a long
	 *
	 * @param j the column as a string in case it is too big to be stored in a long
	 *
	 * @param val the new value of the i,j'th entry
	 *
	 *
	 * */
	void write(long i, long j, double val);
	/**
	 * @param i the row
	 *
	 * @param j the column
	 *
	 * @param val the new value of the i,j'th entry
	 *
	 * */
	void write(string i, string j, double val, string name = "");

	vector<vector<std::string>> getrow(string i);

	void del(string i, string j);
};
