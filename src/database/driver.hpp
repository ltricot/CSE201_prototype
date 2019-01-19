#pragma once

#include <vector>
#include <string>
#include "Vectors.h"
#include "Eigen/Eigen"
#include <unordered_map>
#include <sstream>
#include <map>
#include <set>

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

    /// @brief Return all the keys stored in the matrix
    template <class KeyT> std::vector<KeyT> getKeys();

    void storekey(std::string key);
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


// please forgive us
// this is to avoid a link error
static void _() {
    Driver d("");
    d.getKeys<Author>();
    d.getKeys<Paper>();
}


class SummaryAccessor{
    public:
    std::string directory;
    std::string keysfile;
    
    std::vector<Paper> getKeys();
    void storekey(std::string key);

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

    public:
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

    /** @brief constructor of the EdgeAccessor objects.
     * 
     * @param directory name of the database directory we
     * want to read data from
     * @param size size of the internal buffer
     * 
     */
    EdgeAccessor(std::string directory, unsigned int size);

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
    public:
    typedef Eigen::Matrix<double, rank, 1> vec;

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

/** @brief access the accessor to access accessor.access
 * 
 * @details access access access access access access access access
 * access access access access access access access access access access
 * access access access access access access access access access access
 * access access access access access access access access access access
 * :heart:
 */
template <int rank> class VectorAccessorAccessor {
    private:
    VectorAccessor<rank> accessor;
    typedef typename VectorAccessor<rank>::vec vec;

    void put(std::string key, vec val) {
        // replace if already here
        if(buffer.find(key) != buffer.end()) {
            buffer[key] = val;
            return;
        }

        // if there is space, put & ret
        if(buffer.size() < bufferSize) {
            keys.insert(key);
            (buffer[key] = val);
            return;
        }

        // replace random & ret
        int k = rand() % (buffer.size());
        auto it = keys.begin();
        std::advance(it, k);
        keys.erase(it);
        buffer.erase(key);

        keys.insert(key);
        buffer[key] = val;
        return;
    }

    vec get(std::string key) {
        // ret buf if found is all
        if(buffer.find(key) != buffer.end())
            return buffer[key];

        // if there is space, put & ret
        vec val = accessor.get_vector(Author(key));
        if(buffer.size() < bufferSize) {
            keys.insert(key);
            return (buffer[key] = val);
        }

        // replace random & ret
        int k = rand() % (buffer.size());
        auto it = keys.begin();
        std::advance(it, k);
        keys.erase(it);
        buffer.erase(key);

        keys.insert(key);
        return (buffer[key] = val);
    }

    int bufferSize;
    std::unordered_map<std::string, vec> buffer;
    std::set<std::string> keys;

    public:
    VectorAccessorAccessor(std::string vdata, unsigned int size)
        : accessor(vdata), bufferSize(size) {}

    /// @brief store that shit real fast
    ~VectorAccessorAccessor() {
        // papers are authors and authors are papers
        for (auto& [key, val] : buffer)  // ain't we cool
            accessor.send_vector(Author(key), val);
    }

    void put(Author author, vec val) { put(author.name, val); }
    vec get(Author author) { return get(author.name); }

    void put(Paper paper, vec val) { put(paper.id, val); }
    vec get(Paper paper) { return get(paper.id); }
};
