#include <vector>
#include <string>

#include <Eigen/Eigen>

#include "primitives.h"


/** @brief Template for a generic undirected edge representation
 */
template <typename F, typename T> class Edge_t {
    public:
    F from;
    T to;
    double weight;

    Edge(F from, T to, double weight=1.0)
        : from(from), to(to), weight(weight) {}
};


typedef Edge_t<Author, Paper> Edge;


template <typename F, typename T> class Driver {
    public:

    // convenience
    typedef Edge_t<F, T> Edge;

    // constructor
    Driver(std::string directory);

    /// @brief get all edges outwards from ``from``
    std::vector<Edge> getFrom(F from);
    bool writeEdge(Edge edge);  // overwrites
    bool removeEdge(Edge edge);

    // batch equivalents of above
    std::vector<Edge> getFroms(std::vector<F> froms)
    bool writeEdges(std::vector<Edge> edges);
    bool removeEdges(std::vector<Edge> edges);
};


/** @brief Interface between the recommendation algorithms and the
 * database storing an interaction matrix.
 * 
 * @details This class solves 2 problems:
 *  - it decides of the order of updates (which edge should our
 *    system see and when)
 *  - it optimizes database interaction through some sort of batching
 * Its main interface is an infinite iterator.
 */
class EdgeAccessor {
    private:
    Driver<std::string, std::string> driver;

    /// stores the size of the internal buffer
    unsigned int bufferSize;

    /// stores edges to send when ``getBatch`` is called
    /// there is no need for this to be a vector. maybe making it some sort
    /// of priority queue may be wise
    std::vector<Edge_t> replayBuffer;

    /** @brief Update the internal buffer by interacting with the database
     * 
     * @details This method will be called more or less often in order to
     * update the edges contained in the internal buffer. Edges already in
     * the buffer may be thrown away according to some schedule or uniformly
     * at random so as to keep the buffer of size inferior to ``bufferSize``.
     * 
     * @param proportion how much of the buffer should be replaced ; should
     * be between 0 and 1.
     */
    void updateBuffer(float proportion);

    public:
    EdgeAccessor(std::string directory, unsigned int size)
        : driver(Driver(directory)), bufferSize(size) {
        updateBuffer(1.0);  // initialize buffer
    }

    class iterator : public std::iterator<
            std::input_iterator_tag,
            Edge_t, int, const Edge_t*, Edge_t> {
        // stuff
    };

    iterator begin();
    iterator end();
};


template <int rank> class VectorAccessor {
    typedef Matrix<double, rank, 1> vec;

    vec get_vector(Author author);
    vec get_vector(Paper paper);

    bool send_vector(Author author, vec);
    bool send_vector(Paper paper, vec);
};
