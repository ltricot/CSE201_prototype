#include "references.hpp"


int main(int argc, char *argv[]) {
    std::vector<std::string> archives;
    for(int i = 2; i < argc; i++)
        archives.push_back(std::string(argv[0]));

    setUpReferences(std::string(argv[1]), archives);

    // serialize allReferences in some kinf of way
}
