#include <fstream>
#include <string>

#include "primitives.hpp"


// typedef std::pair<Paper, Paper> Reference;

class Archive {
    private:

    std::string temp_pdf_folder;
    std::string s3path, graph;
    void download();
    void decompress();

    public:

    Archive(std::string s3path, std::string graph);

    void run();
};


class Extractor {
    private:

    std::vector<Reference> references;

    public:

    Extractor(std::string fpath);

    std::vector<Reference>::iterator begin() { return references.begin(); }
    std::vector<Reference>::iterator end() { return references.end(); }
};

// open ifstream before and close after
std::string pdfToText(std::ifstream &pdf);
