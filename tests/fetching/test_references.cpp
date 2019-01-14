#include references.hpp

TEST_CASE("fetching/references/readFile,fetching/references/writeFile", "test if it reads what we write exactly in the same way"){
    std::string filename;
    filename ="test";
    std::map<std::string, std::vector<std::string>> data ;

    data = <"Loan is cool", "maria as well">;


    
    REQUIRE(references.writeFile(data, std::map<std::string, filename) == references.readFile(filename)
}
//Not finished and not correct
