#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "kortchemski.cpp"
#include "testmain.hpp"
#include "fetching/crawler.hpp"


TEST_CASE("fetching/crawler/getPairs", "test whether XML is well parsed to fetch author / paper edges") {
    std::vector<Edge> edges;
    Crawler crawler;

    edges = crawler.getPairs(kortchemski);

    // there are 12 authors  mentioned in the file
    REQUIRE(edges.size() == 12);
}
