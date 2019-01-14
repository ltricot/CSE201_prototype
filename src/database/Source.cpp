/*#include <was/storage_account.h>
#include <was/table.h>*/
#include <iostream>
#include <string>
#include "ReferencesReader.h"
#include "driver.hpp"
using namespace std;


int main() {
	ReferencesReader r("References.txt");
	Matrix m = r.MakeMatrix();
	cout << m.read("37", "2313072105") << endl;
	m.write("37", "41234", 2, "Marie");
	m.del("37", "41234");
	Author a("Bernard");
	Paper p("Bernardism in everyday life");
	Edge e(a, p);
	Driver d;
	d.writeEdge(e);

	VectorAccessor<3> v;
    Eigen::Matrix<double, 3, 1> vec;
    vec << 1, 2, 3;
	bool b = v.send_vector(a, vec);
    cout <<  v.get_vector(a);
	return 0;
}
