#ifndef TOOLS_H
#define TOOLS_H

#include <string>

std::string get(std::string url);
std::string post(std::string url, std::string body);
std::string put(std::string url, std::string body);

#endif // TOOLS_H
