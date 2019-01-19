//#include <was/storage_account.h>
#include "ReferencesReader.h"
#include "driver.hpp"
#include <iostream>
#include <string>
//#include <was/table.h>
#include <Eigen>

using namespace std;

const int lat_feat = 10;

class mat_factorization {
  public:
    // Data Members

    double alpha, beta;

    // Constructor
    mat_factorization(double a, double b) {
        alpha = a;
        beta = b;
    }

    void regularized_update(Edge e) {
        VectorAccessor<lat_feat> v; // not the proper way to use VectorAccessor

        // Get Vectors
        Eigen::MatrixXd P_auth = v.get_vector(e.author);
        Eigen::MatrixXd Q_pap = v.get_vector(e.paper);

        Eigen::MatrixXd m = P_auth.transpose() * Q_pap;
        double approx_value = m(0, 0);

        double eij = e.weight - approx_value;
        std::cout << eij << std::endl;
        // Update Vectors

        for (int k = 0; k < lat_feat; k++) {
            P_auth(k, 0) += 2 * alpha * (eij * Q_pap(k, 0) - beta * P_auth(k, 0));
            Q_pap(k, 0) += 2 * alpha * (eij * P_auth(k, 0) - beta * Q_pap(k, 0));
        }

        // Send Vectors
        v.send_vector(e.author, P_auth);
        v.send_vector(e.paper, Q_pap);
    }
};

#ifdef asupprimer 
int main() {
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
    return 0;
}
#endif