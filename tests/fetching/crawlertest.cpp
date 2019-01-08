#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "crawler.hpp"
#include "kortchemski.cpp"
#include "testmain.hpp"

TEST_CASE("fetching/crawler/getPairs",
          "test whether XML is well parsed to fetch author / paper edges") {
    std::vector<Edge> edges;
    Crawler crawler;

    edges = crawler.getPairs(kortchemski);

    // there are 12 authors  mentioned in the file
    REQUIRE(edges.size() == 12);
}

TEST_CASE("fetching/crawler/getID", "test getID on different arxiv urls") {
    std::vector<std::string> urls = {
        "http://arxiv.org/abs/0804.0446v3", "http://arxiv.org/abs/1106.0271v4",
        "http://arxiv.org/abs/1109.4138v3", "http://arxiv.org/abs/1110.2163v4",
        "http://arxiv.org/abs/1205.3145v4", "http://arxiv.org/abs/1312.4933v2",
        "http://arxiv.org/abs/1312.5678v3", "http://arxiv.org/abs/1504.04358v2",
        "http://arxiv.org/abs/1307.6818v3", "http://arxiv.org/abs/1412.1068v2"};

    std::vector<std::string> ids = {"0804.0446v3", "1106.0271v4", "1109.4138v3", "1110.2163v4",
                                    "1205.3145v4", "1312.4933v2", "1312.5678v3", "1504.04358v2",
                                    "1307.6818v3", "1412.1068v2"};

    // ugly iteration :(
    for (int i = 0; i != urls.size(); i++) {
        REQUIRE(getID(urls[i]) == ids[i]);
    }
}

TEST_CASE("fetching/crawler/fromAuthors", "test arxiv query with author as parameter") {
    Crawler crawler;
    std::vector<Author> authors = {Author("kortchemski")};
    auto edges = crawler.fromAuthors(authors);
    REQUIRE(edges.size() == 12);
}

TEST_CASE("fetching/crawler/getSummary", "test if getSummary gets all the summaries") {
    Crawler crawler;
    std::vector<Paper> summaries = crawler.getSummary(kortchemski);
    std::cout << "i am here" << summaries.size() << std::endl;

    REQUIRE(summaries.size() == 10);

    std::vector<std::string> summ = {
        summary1, summary2, summary3, summary4, summary5, 
        summary6, summary7, summary8, summary9, summary10};

    for (int i = 0; i != summ.size(); i++) {
        REQUIRE(summaries[i].summary == summ[i]);
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
