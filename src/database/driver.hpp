#include <vector>
#include <string>
#include "vectors.h"
#include <Eigen/Eigen>
#include <unordered_map>
#include <sstream>

#include "primitives.h"

using namespace std;
/** @brief Template for a generic undirected edge representation
 */


class Driver {
    public:

	std::string directory;
	/// @brief get all edges outwards from ``from``
	std::vector<Edge> getFrom(Author from);
	bool writeEdge(Edge edge);  // overwrites
	bool removeEdge(Edge edge);

	// batch equivalents of above
	std::vector<Edge> getFroms(std::vector<Author> froms);
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

    vec get_vector(Author author){
        Vectors v("Authors");
        string n = author.name;
        hash<string> hasher;
        size_t foo = hasher(n);
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.getvector<rank> (id);
    }

    vec get_vector(Paper paper){
        Vectors v("Papers");
        string n = paper.id;
        hash<string> hasher;
        size_t foo = hasher(n);
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.getvector<rank> (id);
    }

    bool send_vector(Author author, vec){
        Vectors v("Authors");
        string n = author.id;
        hash<string> hasher;
        size_t foo = hasher(n);
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.storevector<rank> (id, vec);
        return true;
    }
    bool send_vector(Paper paper, vec){
        Vectors v("Papers");
        string n = paper.id;
        hash<string> hasher;
        size_t foo = hasher(n);
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.storevector<rank> (id, vec);
        return true;        
    }
};
