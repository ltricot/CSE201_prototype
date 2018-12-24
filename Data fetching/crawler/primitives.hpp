#include <algorithm>
#include <string>


class Author {
    /**
     * Contains all information on a paper we ever need to store, or use.
     */

    public:
    std::string name;

    Author(std::string name) : name(name) {}
};

class Paper {
    /**
     * Contains all information on a paper we ever need to store, or use.
     * We do not store paper authors or references to other papers here as
     * those are only used to construct edges.
     */

    public:
    std::string id;
    std::string summary;

    Paper(std::string id, std::string summary="") : id(id), summary(summary) {}
};

// from: first. to: second.
typedef std::pair<Paper, Paper> Reference;

// type of an edge between and author and a paper
typedef std::pair<Author, Paper> Edge;
