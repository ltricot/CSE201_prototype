#pragma once
#include <was/storage_account.h>
#include <was/table.h>
#include <string>
#include <vector>
using namespace std;
class Paper {
public:
	int date;
	int id;
	string title;
	string author;
	azure::storage::table_entity entity;
	Paper(string tit, string a, string top, int d, int id);
	Paper(vector<string> line);
	azure::storage::table_result upload(azure::storage::cloud_table& table);
};