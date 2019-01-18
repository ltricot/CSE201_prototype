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


// we should have made a template <class F, class T> where F an T
// are key type and value type
// but we didn't and now there is no time
class Driver {
    public:
	std::string directory;
    std::string keysfile;

    template <class KeyT> std::vector<KeyT> getKeys();

	/// @brief get all edges outwards from ``from``
	std::vector<Edge> getFrom(Author from);
    std::vector<Reference> getFrom(Paper paper);
    std::vector<Friends> getFrom(Author from, bool fr);  // yes i know this is bad

    /// @brief Store an edge in the Matrix
	bool writeEdge(Edge edge);  // overwrites
	bool writeEdge(Reference ref);
    bool writeEdge(Friends friends);

    /// @brief Remove an edge from the Matrix
    bool removeEdge(Edge edge);
    bool removeEdge(Reference ref);
    bool removeEdge(Friends friends);

	/// @brief batch equivalents of writeEdge
	std::vector<Edge> getFroms(std::vector<Author> froms);
	bool writeEdges(std::vector<Edge> edges);
    bool writeEdges(std::vector<Reference> refs);
    bool writeEdges(std::vector<Friends> friends );

    /// @brief batch equivalent of removeEdge
	bool removeEdges(std::vector<Edge> edges);
    bool removeEdges(std::vector<Reference> refs);
    bool removeEdges(std::vector<Friends> friends);

    Driver(std::string dir);
};


class SummaryAccessor{
    public:
    std::string directory;
    std::string keysfile;
    
    std::vector<Paper> getKeys();
    SummaryAccessor(std::string dir);
    
    /// @brief Store the summary related to paper
    void sendSummary(Paper paper);
    
    /// @brief Recover the summary of a given paper
    std::string getSummary(Paper paper);
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

    // stores some authors fetched from the database
    std::vector<Author> someAuthors ; 

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
    /** @brief constructor of the EdgeAccessor objects.
     * 
     * @param directory name of the database directory we
     * want to read data from
     * @param size size of the internal buffer
     * 
     */
    EdgeAccessor(std::string directory, unsigned int size)
        : driver(Driver(directory)), bufferSize(size) {} 
    
    class iterator : public std::iterator<
            std::input_iterator_tag,
            Edge, int, const Edge*, Edge> {
        
        private:
        int cursor;
        EdgeAccessor *parent;
        
        public:
        iterator(EdgeAccessor *parent): parent(parent), cursor(0){}
        iterator operator++();
        Edge operator*();
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

    /// @brief get the vector of an author
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

    /// @brief get the vector of a paper
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

    /// @brief Store the vector of an author
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

    /// @brief Store the vector of a Paper
    bool send_vector(Paper paper, vec vect) {
        Vectors v(directory);
        string n = paper.id;
        hash<string> hasher;
        size_t foo = hasher(n);
        foo = foo % 100000000000LU;
	    std::ostringstream ostr;
	    ostr << foo;
	    string id = ostr.str();
        v.storevector<rank> (id, vect);
        return true;        
    }
};
