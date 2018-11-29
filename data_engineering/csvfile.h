#pragma once
#include <string>
#include <vector>

class CSVfile {
public:
	std::string filename;
	CSVfile(std::string name) {
		this->filename = name;
	}
	std::vector<std::vector<std::string>> read();
	void print();
};
