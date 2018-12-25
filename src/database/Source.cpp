#include <was/storage_account.h>
#include <was/table.h>
#include <iostream>
#include <string>
#include "Paper.h"
#include "PapersReader.h"
#include "ReferencesReader.h"

using namespace std;


int main() {
	ReferencesReader r("References.txt");
	Matrix m =  r.MakeMatrix();
	cout << m.read("37","2313072105") << endl;
	return 0;
}
