#pragma once
#include "Vectors.h"

using namespace std;
Vectors::Vectors(string dir) {
    this->root_directory = dir;
    int res = _mkdir(dir.c_str());//, 0666);
}