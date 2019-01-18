#pragma once
#include <string>
#include <vector>

/** @brief Objects which turns a text file into a matrix
 */
class Reader {

public:
	///@brief The file's name
	std::string filename; 

	///@brief Column seperator, by default it is the comma.
	std::string delim; 


	Reader();
	Reader(std::string name); 
	Reader(std::string name, std::string delimeter);

	/** @brief Returns a matrix of strings from the file
	 * 
	 * @details Seperates columns based on delim, and lines based on line breaks
	 */
	std::vector<std::vector<std::string>> read(); 

	/** @brief Prints the content of the file in the console
	 * 
	 * @details mainly for debugging
	 */
	void print();
};

