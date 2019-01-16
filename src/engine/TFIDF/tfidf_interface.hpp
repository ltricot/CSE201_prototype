#include <vector>
#include <tuple>

#include "primitives.hpp"


class TFIDF {
    public:

    TFIDF();
    void updateSummaries(std::vector<Paper> papers);

    // type of a word to paper interaction
    typedef std::tuple<std::string, Paper, double> pEdge;
    class iterator : public std::iterator<
            std::input_iterator_tag,
            pEdge, int, const pEdge*, pEdge> {

        public:
        iterator();

        // make it so next pEde is available
        iterator operator++();

        /**
         * For it != crawler.end()?
         * This is an infinite iterator and so there is no end condition.
         */
        bool operator==(iterator other) const { return false; }
        bool operator!=(iterator other) const { return true; }

        // get next pEdge
        pEdge operator*() const;
    };

    iterator begin();
    iterator end();
};


class Summaries {
    public:

    class iterator : public std::iterator<
            std::input_iterator_tag,
            Paper, int, const Paper*, Paper> {

        public:
        iterator();

        // make it so next pEde is available
        iterator operator++();

        /**
         * For it != crawler.end()?
         * This is an infinite iterator and so there is no end condition.
         */
        bool operator==(iterator other) const { return false; }
        bool operator!=(iterator other) const { return true; }

        // get next pEdge
        Paper operator*() const;
    };

    iterator begin();
    iterator end();
};

// std::get<0>(tup) == tup[0]
