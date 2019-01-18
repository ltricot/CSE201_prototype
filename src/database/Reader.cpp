#include "Reader.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

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
    std::vector<std::vector<std::string>> ret;
    if (!fs::exists(filename))
        return ret;

    std::ifstream file(filename);
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
    for (std::vector<std::string> vec : data) {
        for (std::string data : vec) {
            std::cout << data << " , ";
        }
        std::cout << std::endl;
    }
}
