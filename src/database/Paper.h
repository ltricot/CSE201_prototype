#pragma once
#include <was/storage_account.h>
#include <was/table.h>
#include <string>
#include <vector>
using namespace std;
/**
 *  @brief Basically a wrapper class for azure table entitities */
class Paper {

public:
	//Year of publication of the paper
	int date; 

	// Unique identifier of the paper, also its index in the adjacency matrix
	int id; 
	
	// Title of the paper
	string title; 
	
	//Author of the paper
	string author; 
	
	//Azure table entry
	azure::storage::table_entity entity; 
	/** @brief Constructor for paper object
	 * 
	 * @param tit Title of the paper
	 * 
	 * @param a Author of the paper
	 * 
	 * @param top Topic
	 * 
	 * @param d Date 
	 * 
	 * @param id Unique identifier of the paper */
	Paper(string tit, string a, string top, int d, int id);
	
	/** @brief Constructor for paper object from a line in the Papers.txt file from the Microsoft Academic Graph */
	Paper(vector<string> line); 
	
	/** @brief Upload the paper to an Azure table
	 * 
	 * @details 
	 *
	 * @param table reference to the azure table on which the paper information will be stored 
	 * 
	 * @return The outcome of the upload operation 
	 * */
	azure::storage::table_result upload(azure::storage::cloud_table& table); 
}
