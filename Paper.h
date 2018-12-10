#pragma once
#include <was/storage_account.h>
#include <was/table.h>
#include <string>
using namespace std;
class Paper {
public:
	int date;
	int id;
	string title;
	string author;
	string topic;
	azure::storage::table_entity entity;
	Paper(string tit, string a, string top, int d, int id);
	azure::storage::table_result upload(azure::storage::cloud_table& table);
};