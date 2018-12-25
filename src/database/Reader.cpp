#include "Reader.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

Reader::Reader() {
	this->filename = " ";
	this->delim = ",";
}
Reader::Reader(std::string name) {
	this->filename = name;
	this->delim = ",";
}

Reader::Reader(std::string name, std::string delimeter) {
	this->filename = name;
	this->delim = delimeter;
}

std::vector<std::vector<std::string>> Reader::read() {
	std::ifstream file(filename);
	std::vector<std::vector<std::string>> ret;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(","));
		ret.push_back(vec);
	}

	file.close();
	return ret;
}

void Reader::print() {
	std::vector<std::vector<std::string>> data = this->read();
	for (std::vector<std::string> vec : data)
	{
		for (std::string data : vec)
		{
			std::cout << data << " , ";
		}
		std::cout << std::endl;
	}
}
