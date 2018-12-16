#include <algorithm>
#include <string>


class Author {
    public:
    std::string name;
};

class Paper {
    public:
    std::string id;
};

// from: first. to: second.
typedef std::pair<Paper, Paper> Reference;

// type of an edge between and author and a paper
typedef std::pair<Author, Paper> Edge;
