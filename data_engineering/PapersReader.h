#pragma once
#include "Paper.h"
#include "Reader.h"
#include <string>

class PapersReader : public Reader {
/* Specialized reader for a file containing information on a list of research papers */ 
public:
	std::string filename; /*The file name */
	PapersReader(std::string name); 
	void UploadPapers(azure::storage::cloud_table& table); /* Creates a Paper object from each line and uploads it */
};
