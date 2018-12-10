#pragma once
#include <string>
#include <vector>

class Reader {
public:
	std::string filename;
	std::string delim;
	Reader();
	Reader(std::string name);
	Reader(std::string name, std::string delimeter);
	std::vector<std::vector<std::string>> read();
	void print();
};

