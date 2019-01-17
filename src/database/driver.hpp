#pragma once

#include <vector>
#include <string>
#include "Vectors.h"
#include "Eigen/Eigen"
#include <unordered_map>
#include <sstream>

#include "primitives.hpp"


using namespace std;
/** @brief Template for a generic undirected edge representation
 */


class Driver {
    public:
	std::string directory;

	/// @brief get all edges outwards from ``from``
	std::vector<Edge> getFrom(Author from);
    std::vector<Reference> getFrom(Paper paper);

	bool writeEdge(Edge edge);  // overwrites
	bool writeEdge(Reference ref);

    bool removeEdge(Edge edge);
    bool removeEdge(Reference ref);

	// batch equivalents of above
	std::vector<Edge> getFroms(std::vector<Author> froms);
	bool writeEdges(std::vector<Edge> edges);
    bool writeEdges(std::vector<Reference> refs);

	bool removeEdges(std::vector<Edge> edges);
    bool removeEdges(std::vector<Reference> refs);
    Driver(std::string dir);
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
    Driver driver;

    /// stores the size of the internal buffer
    unsigned int bufferSize;

    /// stores edges to send when ``getBatch`` is called
    /// there is no need for this to be a vector. maybe making it some sort
    /// of priority queue may be wise
    std::vector<Edge> replayBuffer;

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
            Edge, int, const Edge*, Edge> {
        // stuff
    };

    iterator begin();
    iterator end();
};


template <int rank> class VectorAccessor {
    typedef Eigen::Matrix<double, rank, 1> vec;

  public:
    string directory;
	VectorAccessor(string dir) {
        this->directory = dir;
        int res = mkdir(dir.c_str(), 0666);
	}

	vec get_vector(Author author){
        Vectors v(directory);
        string n = author.name;
        hash<string> hasher;
        size_t foo = hasher(n);                
        foo = foo % 100000000000LU;
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        vec tmp =  v.getvector<rank> (id);
	    vec p = (Eigen::MatrixXd::Random(rank, 1) + Eigen::MatrixXd::Constant(rank,1, 1.))*0.5;
        if (tmp(1, 0) == -DBL_MAX) {
		    this->send_vector(author, p);
            return p;
		}        
        return tmp;
    }

    vec get_vector(Paper paper){
        Vectors v(directory);
        string n = paper.id;
        hash<string> hasher;
        size_t foo = hasher(n);
        foo = foo % 100000000000LU;
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        vec tmp  =  v.getvector<rank> (id);
	    vec p = (Eigen::MatrixXd::Random(rank, 1) + Eigen::MatrixXd::Constant(rank,1, 1.))*0.5;
        if (tmp(1, 0) == -DBL_MAX) {
    		this->send_vector(paper, p);
            return p;
		}        
        return tmp;
    }

    bool send_vector(Author author, vec vect) {
        Vectors v(directory);
        string n = author.name;
        hash<string> hasher;
        size_t foo = hasher(n);
        foo = foo % 100000000000LU;
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.storevector<rank> (id, vect);
        return true;
    }

    bool send_vector(Paper paper, vec vect) {
        Vectors v(directory);
        string n = paper.id;
        hash<string> hasher;
        size_t foo = hasher(n);
        foo = foo % 100000000000 LU;
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.storevector<rank> (id, vect);
        return true;        
    }
};
