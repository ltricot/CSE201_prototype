#include "PapersReader.h"
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

PapersReader::PapersReader(std::string name) {
	this->filename = name;
	this->delim = "\t";
}

void PapersReader::UploadPapers(azure::storage::cloud_table& table){
	std::ifstream file(filename);
	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(this->delim));
		Paper p(vec);
		p.upload(table);
	}
}