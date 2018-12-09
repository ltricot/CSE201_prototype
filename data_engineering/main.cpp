#include <string>
#include <iostream>
#include "csvfile.h"

int main() {
	CSVfile example("example.csv");
	example.print();
	return 0;
}
