#include references.hpp

TEST_CASE("fetching/references/readFile,fetching/references/writeFile", "test if it reads what we write exactly in the same way"){
    std::string filename;
    filename ="test";
    std::map<std::string, std::vector<std::string>> data ;

    data["paper_1"].push_back("reference_1/reference_2/reference_3");
    data["paper_2"].push_back("reference_4/reference_5/reference_6");

    REQUIRE(references.writeFile(data, filename) == references.readFile(filename));
}
//Not finished and not correct
