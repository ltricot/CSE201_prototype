#pragma once
#include "Paper.h"
#include "Reader.h"
#include <string>

class PapersReader : public Reader {
public:
	std::string filename;
	PapersReader(std::string name);
	void UploadPapers(azure::storage::cloud_table& table);
};