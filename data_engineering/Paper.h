#pragma once
#include <was/storage_account.h>
#include <was/table.h>
#include <string>
#include <vector>
using namespace std;
class Paper {
/* Basically a wrapper class for azure table entitities */
public:
	int date; /*Year of publication of the paper*/
	int id; /*Unique identifier of the paper, also its index in the adjacency matrix*/
	string title; /* Title of the paper*/
	string author; /*Authot of the paper */
	azure::storage::table_entity entity; /*Azure table entry */
	Paper(string tit, string a, string top, int d, int id);
	Paper(vector<string> line); /*Constructor for paper object from a line in the Papers.txt file from the Microsoft Academic Graph */
	azure::storage::table_result upload(azure::storage::cloud_table& table); /*Upload the paper on an Azure table */
};
