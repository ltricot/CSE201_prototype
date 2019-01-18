#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#pragma once
#include <algorithm>
#include <string>


class Author {
    /** @brief Contains all information on a paper we ever need to store or use.
     */

    public:
    std::string name;

    Author(std::string name) : name(name) {}
};

class Paper {
    /** @brief Contains all information on a paper we ever need to store, or use.
     *
     * @details We do not store paper authors or references to other papers here as
     * those are only used to construct edges.
     */

    public:
    std::string id;
    std::string summary;

    Paper(std::string id, std::string summary="") : id(id), summary(summary) {}
};

class Edge {
    /** @brief Store an edge between a paper and an author.
     */

    public:
    Author author;
    Paper paper;
    double weight;

    Edge(Author author, Paper paper, double weight=1.0)
        : author(author), paper(paper), weight(weight) {}
};

// from: first. to: second.
typedef std::pair<Paper, Paper> Reference;


#endif // PRIMITIVE_H
