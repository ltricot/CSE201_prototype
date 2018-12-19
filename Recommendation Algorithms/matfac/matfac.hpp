#include <vector>
#include <Eigen/Dense>
using namespace Eigen;


typedef std::pair<int, int> Edge;

template <int rank> class Factorizer {
    public:
    std::vector<Matrix<double, rank, 1>> users;
    std::vector<Matrix<double, rank, 1>> objects;

    Factorizer(unsigned int users, unsigned int objects);
    double loss(std::vector<Edge> edges);
    void train(std::vector<Edge> edges, double lr);
};
