#include <vector>
#include <string>


template <typename F, typename T> class Edge {
    /** @brief Template for a generic undirected edge representation
     */

    public:
    F from;
    T to;
    double weight;

    Edge(F from, T to, double weight=1.0)
        : from(from), to(to), weight(weight) {}
};

class EdgeAccessor {
    /** @brief Interface between the recommendation algorithms and the
     * database storing an interaction matrix.
     * 
     * @details This class solves 2 problems:
     *  - it decides of the order of updates (which edge should our
     *    system see and when)
     *  - it optimizes database interaction through some sort of batching
     * Its main interface is an infinite iterator.
     */
    private:
    /// stores the size of the internal buffer
    unsigned int bufferSize;
    typedef Edge<std::string, std::string> Edge_t;

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
    EdgeAccessor(unsigned int size) : bufferSize(size) {
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
