#include <was/storage_account.h>
#include <was/table.h>
#include <string>
#include <iostream>
#include "csvfile.h"

int main() {
	CSVfile example("example.csv");
	std::vector<std::vector<std::string>> ex = example.read();
	for (std::vector<std::string> vec : ex)
	{
		for (std::string data : vec)
		{
			std::cout << data << " , ";
		}
		std::cout << std::endl;
	}
	return 0;
}