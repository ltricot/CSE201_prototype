#include "references.hpp"


int main(int argc, char *argv[]) {
    std::map<std::string, std::vector<std::string>> references;

    std::vector<std::string> archives;
    for(int i = 3; i < argc; i++)
        archives.push_back(std::string(argv[0]));

    references = setUpReferences(std::string(argv[1]), archives);
    writeFile(references, argv[2]);
}
