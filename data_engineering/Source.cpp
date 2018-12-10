#include <was/storage_account.h>
#include <was/table.h>
#include <iostream>
#include <string>
#include "Paper.h"
#include "PapersReader.h"
using namespace std;


int main() {
	const utility::string_t storage_connection_string = utility::conversions::to_string_t("INSERT KEY HERE");
	
	// Retrieve the storage account from the connection string.
	azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

	// Create the table client.
	azure::storage::cloud_table_client table_client = storage_account.create_cloud_table_client();

	string s("Papers");
	// Retrieve a reference to a table.
	azure::storage::cloud_table table = table_client.get_table_reference(utility::conversions::to_string_t(s));
	
	PapersReader R("test.txt");
	R.UploadPapers(table);
	return 0;
}
