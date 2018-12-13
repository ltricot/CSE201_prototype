#pragma once
#include "Reader.h"
class ReferencesReader : public Reader {
public:
	std::string filename;
	ReferencesReader(std::string name);
	void MakeMatrix();
};