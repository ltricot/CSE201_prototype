#include <string>
#include <Eigen/core>
#include <map>
#include "primitives.hpp"

#ifdef pasbesoin
class Author {
    public:
    std::string name;
};

class Paper {
    public:
    std::string id;
};

typedef std::pair<Author, Paper> Edge;
#endif


class Factorizer {
    private:
    // row matrices
    typedef std::vector<Eigen::RowVectorXf> vectors;
    vectors authors;
    vectors papers;
    vectors tfidf;

    // don't worry about this right now
    std::map<Author, int> authorIndex;
    std::map<Paper, int> paperIndex;

    public:
    // initialize authors & papers randomly
    // store tfidf
    Factorizer(vectors tfidf);

    // each argument is an index in your matrices
    void update(int author, int paper, float lr);

    // update over iterable
    template <class Iterable> void train(Iterable data) {
        Iterable::iterator it;
        for (it = data.begin(); it != data.end(); it++) {
            // call update; ``*it`` is an Edge
        }
    }
};


/*
 * std::vector<int> numbers;
 * std::vector<int>::iterator i;
 *
 * for (i = numbers.begin(); i != numbers.end(); i++) {
 *     std::cout << *i << std::endl;
 * }
 */
