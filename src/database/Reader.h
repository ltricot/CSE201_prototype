#pragma once
#include <string>
#include <vector>

class Reader {
	/*Object which reads a table stored in a file*/
public:
	std::string filename; /*The file's name */
	std::string delim; /* What delimits the columns */
	Reader();
	Reader(std::string name); /*By default the delimeter is a comma */
	Reader(std::string name, std::string delimeter);
	std::vector<std::vector<std::string>> read(); /*Returns a matrix of the entries in the .txt file*/
	void print();
};

