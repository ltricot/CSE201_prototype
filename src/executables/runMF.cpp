// what header file should I include? 
// the class mat_factorization is defined in the following files:
// mat_fac_eigen.cpp

#include "driver.hpp"
#include "ReferencesReader.h"
#include <iostream>

int main(int argc, char const *argv[]){
    std::string cdata = argv[1];
    std::string vdata = argv[2];

    Driver cdriver(cdata);
    Driver vdriver(vdata);


    // Testing the database
    ReferencesReader r("CSE201_prototype\src\database\References.txt");
    vector<Edge> foo;
    foo = r.GetEdges();
    for (vector<Edge>::iterator it = foo.begin(); it < foo.end(); it++) {
        std::cout << (*it).author.name << endl;
    }
    
    Matrix m = r.MakeMatrix();
    /*cout << m.read("37", "2313072105") << endl;
    m.write("37", "41234", 2, "Marie");
    m.del("37", "41234"); */

    // Testing the interface/driver
    Author a("Bernard");
    VectorAccessor<200> v;
    v.send_vector(a, Eigen::MatrixXd::Constant(200, 1, 1.));
    Paper p("Bernardism in everyday life");
    Edge e(a, p);
    Driver d;
    d.writeEdge(e);

    mat_factorization M(0.02, 0.002);
    for (int j = 0; j < 1000; j++) {

        for (vector<Edge>::iterator it = foo.begin(); it < foo.end(); it++) {
            M.regularized_update(*it);
        }
    }





}
