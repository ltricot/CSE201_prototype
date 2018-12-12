#include <was/storage_account.h>
#include <was/table.h>
#include <iostream>
#include <string>
#include "Paper.h"
#include "PapersReader.h"
#include "ReferencesReader.h"

using namespace std;


int main() {
	/*const utility::string_t storage_connection_string = utility::conversions::to_string_t("DefaultEndpointsProtocol=https;AccountName=abdelrahmansameh;AccountKey=0KyoXM2pAEIePW34e0zQkEV+M1PDwPs7RdSe1+aT1xo9ZZXCyaGv+tdAYp0rCFkVcq8L/hKCh6puen7PVsihkQ==;EndpointSuffix=core.windows.net");
	
	// Retrieve the storage account from the connection string.
	azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

	// Create the table client.
	azure::storage::cloud_table_client table_client = storage_account.create_cloud_table_client();

	string s("Papers");
	// Retrieve a reference to a table.
	azure::storage::cloud_table table = table_client.get_table_reference(utility::conversions::to_string_t(s));
	
	PapersReader R("test.txt");
	R.UploadPapers(table);*/
	
	ReferencesReader r("References.txt");
	r.MakeMatrix();
	return 0;
}