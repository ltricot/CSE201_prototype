#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int main() {
    /*xml_document<> doc;
    ifstream theFile ("test.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);*/

	xml_document<> doc;
	ifstream file("test.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	// Find our root node
	xml_node<> *pRoot = doc.first_node("feed");
    xml_node<> *pUpdate =pRoot->first_node("update");
    std::cout << pUpdate->value()<<std::endl;
	for(xml_node<> *pAuthor=pRoot->first_node("author"); pAuthor; pAuthor=pAuthor->next_sibling())
	{
		std::cout<< pAuthor->value() <<std::endl;
	}
} 