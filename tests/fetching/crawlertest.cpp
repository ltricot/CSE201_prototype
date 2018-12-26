#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "kortchemski.cpp"
#include "testmain.hpp"
#include "crawler.hpp"


TEST_CASE("fetching/crawler/getPairs", "test whether XML is well parsed to fetch author / paper edges") {
    std::vector<Edge> edges;
    Crawler crawler;

    edges = crawler.getPairs(kortchemski);

    // there are 12 authors  mentioned in the file
    REQUIRE(edges.size() == 12);
}

TEST_CASE("fetching/crawler/getID", "test getID on different arxiv urls") {
    std::vector<std::string> urls = {
        "http://arxiv.org/abs/0804.0446v3",
        "http://arxiv.org/abs/1106.0271v4",
        "http://arxiv.org/abs/1109.4138v3",
        "http://arxiv.org/abs/1110.2163v4",
        "http://arxiv.org/abs/1205.3145v4",
        "http://arxiv.org/abs/1312.4933v2",
        "http://arxiv.org/abs/1312.5678v3",
        "http://arxiv.org/abs/1504.04358v2",
        "http://arxiv.org/abs/1307.6818v3",
        "http://arxiv.org/abs/1412.1068v2"
    };

    std::vector<std::string> ids = {
        "0804.0446v3",
        "1106.0271v4",
        "1109.4138v3",
        "1110.2163v4",
        "1205.3145v4",
        "1312.4933v2",
        "1312.5678v3",
        "1504.04358v2",
        "1307.6818v3",
        "1412.1068v2"
    };

    // ugly iteration :(
    for(int i = 0; i != urls.size(); i++) {
        REQUIRE(getID(urls[i]) == ids[i]);
    }
}

/*
TEST_CASE("fetching/references/getText", "can ``Converter`` convert a pdf to text") {
    std::ifstream pdf("kortchemski.pdf");
    std::stringstream buf;

    buf << pdf.rdbuf();
    PDFConverter converter = PDFConverter(&buf);
    std::string text = converter.getText();

    // test something with the returned value :)
}
*/
