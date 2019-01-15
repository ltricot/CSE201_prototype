/*#include <was/storage_account.h>
#include <was/table.h>*/
#include <iostream>
#include <string>
#include "ReferencesReader.h"
#include "driver.hpp"
using namespace std;


int main() {
	//Testing the database 
	ReferencesReader r("References.txt");
	Matrix m = r.MakeMatrix();
	cout << m.read("37", "2313072105") << endl;
	m.write("37", "41234", 2, "Marie");
	m.del("37", "41234");

	//Testing the interface/driver
	Author a("Bernard");
	Paper p("Bernardism in everyday life");
	Edge e(a, p);
	Driver d;
	d.writeEdge(e);

	return 0;
}
