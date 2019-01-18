/*#include <was/storage_account.h>
#include "ReferencesReader.h"
#include "driver.hpp"
#include <iostream>
#include <string>
#include <was/table.h>*/
using namespace std;

const int lat_feat = 30;

class mat_factorization {
  public:
    // Data Members

    double alpha, beta;
    int num_iterations;

    // Matrix stuff
    double mat_val = 1; // Assuming that this is always 1
    Author auth;
    Paper pap;
    long num_authors;
    long num_papers;

    // Vectors
    Eigen::MatrixXd P_auth;
    Eigen::MatrixXd Q_pap;

    // Constructor
    mat_factorization(double a, double b) {
        alpha = a;
        beta = b;
    }

    void regularized_update(Edge e) {
        VectorAccessor<lat_feat> v;

        // Get Vectors
        P_auth = v.get_vector(e.author);
        Q_pap = v.get_vector(e.paper);

        Eigen::MatrixXd m = P_auth.transpose() * Q_pap;

        double approx_value = m(0, 0);
        double eij = e.weight - approx_value;
        // cout << eij << "\n";
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

int main() {
    // Testing the database
    ReferencesReader r("References.txt");
    vector<Edge> foo;
    foo = r.GetEdges();
    Matrix m = r.MakeMatrix(); /*
     /*cout << m.read("37", "2313072105") << endl;
     m.write("37", "41234", 2, "Marie");
     m.del("37", "41234"); */

    // Testing the interface/driver
    /*Author a("Bernard");

    v.send_vector(a, Eigen::MatrixXd::Constant(lat_feat, 1, 1.));
    cout << v.get_vector(a);*/

    // Paper p("Bernardism in everyday life");

    // Edge e(a, p);

    // Driver d;

    // d.writeEdge(e);
    VectorAccessor<lat_feat> v;
    cout << v.get_vector(Author("37")) << endl;
    cout << endl << endl;
    mat_factorization M(0.02, 0.002);
    for (int j = 0; j < 100; j++) {

        for (vector<Edge>::iterator it = foo.begin(); it < foo.end(); it++) {
            M.regularized_update(*it);
        }
    }
    cout << v.get_vector(Author("37")) << endl;
    return 0;
}
