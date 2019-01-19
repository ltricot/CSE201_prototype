//#include <was/storage_account.h>
#include "ReferencesReader.h"
#include "driver.hpp"
#include <iostream>
#include <string>
//#include <was/table.h>
#include <Eigen/Eigen>

using namespace std;

const int lat_feat = 10;


class mat_factorization {
    private:
    // Data Members
    double alpha, beta;
    VectorAccessorAccessor<lat_feat> v;
    EdgeAccessor edge_acc;
    double moving_avg;

    public:
    // Constructor
    mat_factorization(std::string cdata, std::string vdata, double a, double b)
        : alpha(a), beta(b), v(vdata, 20000), edge_acc(cdata, 10000), moving_avg(0) {}

    void regularized_update(Edge e, bool err=false) {
        // Get Vectors
        Eigen::MatrixXd P_auth = v.get(e.author);
        Eigen::MatrixXd Q_pap = v.get(e.paper);

        Eigen::MatrixXd m = P_auth.transpose() * Q_pap;
        double approx_value = m(0, 0);

        double eij = (e.weight - approx_value);
        moving_avg = moving_avg * .9 + 0.1 * (eij*eij);

        if(err)
            std::cout << moving_avg << std::endl;

        // Update Vectors
        P_auth += 2 * alpha * (eij * Q_pap - beta * P_auth);
        Q_pap += 2 * alpha * (eij * P_auth - beta * Q_pap);

        // Send Vectors
        v.put(e.author, P_auth);
        v.put(e.paper, Q_pap);
    }

    void run() {
        int i = 0;
        for(auto edge = edge_acc.begin();; ++edge) {
            regularized_update(*edge, !(i % 100));

            if((i = i++ % 1000) == 0)
                edge_acc.updateBuffer(0.01);
        }
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