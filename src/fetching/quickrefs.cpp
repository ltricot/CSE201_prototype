#include <cstdio>  // thats the C library <stdio.h>
#include <cstdlib> // thats the C library <stdlib.h>
#include <ctype.h>
#include <regex>
#include <sstream>
#include <string.h>
#include <unistd.h> // thats the unix standard header

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "zlib.h" // zlib compression library

#include "driver.hpp"
#include "quickrefs.hpp"

#define oldchar 15

///////////////////////////////////////////////

// EXTERNAL CODE FROM HERE

// Find a string in a buffer:
static size_t FindStringInBuffer(char *buffer, char *search, size_t buffersize) {
    char *buffer0 = buffer;

    size_t len = strlen(search);
    bool fnd = false;
    while (!fnd) {
        fnd = true;
        for (size_t i = 0; i < len; i++) {
            if (buffer[i] != search[i]) {
                fnd = false;
                break;
            }
        }

        if (fnd)
            return buffer - buffer0;

        buffer = buffer + 1;
        if (buffer - buffer0 + len >= buffersize)
            return -1;
    }

    return -1;
}

// Convert a recent set of characters into a number if there is one.
// Otherwise return -1:
static float ExtractNumber(const char *search, int lastcharoffset) {
    int i = lastcharoffset;
    while (i > 0 && search[i] == ' ')
        i--;
    while (i > 0 && (isdigit(search[i]) || search[i] == '.'))
        i--;

    float flt = -1.0;
    char buffer[oldchar + 5];
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, search + i + 1, lastcharoffset - i);

    if (buffer[0] && sscanf(buffer, "%f", &flt)) {
        return flt;
    }

    return -1.0;
}

// Check if a certain 2 character token just came along (e.g. BT):
static bool seen2(const char *search, char *recent) {
    if (recent[oldchar - 3] == search[0] && recent[oldchar - 2] == search[1] &&
        (recent[oldchar - 1] == ' ' || recent[oldchar - 1] == 0x0d ||
         recent[oldchar - 1] == 0x0a) &&
        (recent[oldchar - 4] == ' ' || recent[oldchar - 4] == 0x0d ||
         recent[oldchar - 4] == 0x0a)) {
        return true;
    }

    return false;
}

// This method processes an uncompressed Adobe (text) object and extracts text.
template <typename outstream> static void ProcessOutput(outstream &ostr, char *output, size_t len) {
    // Are we currently inside a text object?
    bool intextobject = false;

    // Is the next character literal (e.g. \\ to get a \ character or \( to get ( ):
    bool nextliteral = false;

    // () Bracket nesting level. Text appears inside ()
    int rbdepth = 0;

    // Keep previous chars to get extract numbers etc.:
    char oc[oldchar];
    int j = 0;
    for (j = 0; j < oldchar; j++)
        oc[j] = ' ';

    for (size_t i = 0; i < len; i++) {
        char c = output[i];
        if (intextobject) {
            if (rbdepth == 0 && seen2("TD", oc)) {
                // Positioning.
                // See if a new line has to start or just a tab:
                float num = ExtractNumber(oc, oldchar - 5);
                if (num > 1.0) {
                    // fputc(0x0d, file);
                    // fputc(0x0a, file);
                    ostr << (char)0x0d << (char)0x0a;
                }

                if (num < 1.0) {
                    // fputc('\t', file);
                    ostr << '\t';
                }
            }

            if (rbdepth == 0 && seen2("ET", oc)) {
                // End of a text object, also go to a new line.
                intextobject = false;
                // fputc(0x0d, file);
                // fputc(0x0a, file);
                ostr << (char)0x0d << (char)0x0a;
            } else if (c == '(' && rbdepth == 0 && !nextliteral) {
                // Start outputting text!
                rbdepth = 1;
                // See if a space or tab (>1000) is called for by looking
                // at the number in front of (
                int num = ExtractNumber(oc, oldchar - 1);
                if (num > 0) {
                    if (num > 1000.0) {
                        // fputc('\t', file);
                        ostr << '\t';
                    } else if (num > 100.0) {
                        // fputc(' ', file);
                        ostr << ' ';
                    }
                }
            } else if (c == ')' && rbdepth == 1 && !nextliteral) {
                // Stop outputting text
                rbdepth = 0;
            } else if (rbdepth == 1) {
                // Just a normal text character:
                if (c == '\\' && !nextliteral) {
                    // Only print out next character no matter what. Do not interpret.
                    nextliteral = true;
                } else {
                    nextliteral = false;
                    if (((c >= ' ') && (c <= '~')) || ((c >= 128) && (c < 255))) {
                        // fputc(c, file);
                        ostr << (char)c;
                    }
                }
            }
        }

        // Store the recent characters for when we have to go back for a number:
        for (j = 0; j < oldchar - 1; j++)
            oc[j] = oc[j + 1];
        oc[oldchar - 1] = c;

        if (!intextobject) {
            if (seen2("BT", oc)) {
                // Start of a text object:
                intextobject = true;
            }
        }
    }
}

template <typename outstream> void extractText(std::stringstream &istr, outstream &ostr) {
    // put stream in C-style string
    std::string temp;
    temp = istr.str();

    int filelen = temp.length();
    char *buffer = new char[filelen + 1];
    int i = 0;
    for (std::string::iterator c = temp.begin(); c < temp.end(); c++) {
        buffer[i++] = *c;
    }

    buffer[i] = '\0'; // 0 terminated

    // Now search the buffer repeated for streams of data:
    bool morestreams = true;
    while (morestreams) {
        // Search for stream, endstream. We ought to first check the filter
        // of the object to make sure it if FlateDecode, but skip that for now!
        size_t streamstart = FindStringInBuffer(buffer, (char *)"stream", filelen);
        size_t streamend = FindStringInBuffer(buffer, (char *)"endstream", filelen);

        if (streamstart > 0 && streamend > streamstart) {
            // Skip to beginning and end of the data stream:
            streamstart += 6;

            if (buffer[streamstart] == 0x0d && buffer[streamstart + 1] == 0x0a)
                streamstart += 2;
            else if (buffer[streamstart] == 0x0a)
                streamstart++;

            if (buffer[streamend - 2] == 0x0d && buffer[streamend - 1] == 0x0a)
                streamend -= 2;
            else if (buffer[streamend - 1] == 0x0a)
                streamend--;

            // Assume output will fit into 10 times input buffer:
            size_t outsize = (streamend - streamstart) * 10;
            char *output = new char[outsize];
            memset(output, 0, outsize);

            // Now use zlib to inflate:
            z_stream zstrm;
            memset(&zstrm, 0, sizeof(zstrm));

            zstrm.avail_in = streamend - streamstart + 1;
            zstrm.avail_out = outsize;
            zstrm.next_in = (Bytef *)(buffer + streamstart);
            zstrm.next_out = (Bytef *)output;

            int rsti = inflateInit(&zstrm);
            if (rsti == Z_OK) {
                int rst2 = inflate(&zstrm, Z_FINISH);
                if (rst2 >= 0) {
                    // Ok, got something, extract the text:
                    size_t totout = zstrm.total_out;
                    ProcessOutput<outstream>(ostr, output, totout);
                }
            }

            delete[] output;
            output = 0;
            buffer += streamend + 7;
            filelen = filelen - (streamend + 7);
        } else {
            morestreams = false;
        }
    }
}

// EXTERNAL CODE ENDS NOW

std::string pdfToText(std::ifstream &pdf) {
    std::stringstream inp;
    inp << pdf.rdbuf();
    std::stringstream text;
    extractText<std::stringstream>(inp, text);
    return text.str();
}

// id of paper from link to paper on arxiv
static std::string getID(std::string link) {
    std::string temp;
    std::stringstream link_s(link);
    while (std::getline(link_s, temp, '/'))
        ;
    return temp;
}

static std::vector<std::string> findRegex(std::string text, std::string regex) {
    std::smatch m;
    std::regex self_regex(regex);

    std::vector<std::string> res;

    while (std::regex_search(text, m, self_regex)) {
        res.push_back(m.str());
        text = m.suffix().str();
    }

    return res;
}

Extractor::Extractor(std::string fpath) {
    Paper paper = Paper(getID(fpath.substr(0, fpath.size() - 4)));

    std::ifstream infile(fpath);
    std::string text = pdfToText(infile);
    infile.close();

    std::string regex;
    regex = R"(arXiv:\d{4}[.](\d{4,5}[v]\d+|\d{4,5}))"; // taking account of version
    std::vector<std::string> papers = findRegex(text, regex);
    for (std::vector<std::string>::iterator pap = papers.begin(); pap != papers.end(); pap++) {
        references.push_back(std::make_pair(paper, Paper(pap->substr(6, pap->size()))));
    }
}

Archive::Archive(std::string s3path, std::string graph)
    : s3path(s3path), graph(graph), temp_pdf_folder("./temp") {}

void Archive::run() {
    download();
    decompress();

    Driver driver(graph);
    for (auto &p : fs::recursive_directory_iterator(temp_pdf_folder)) {
        std::string s = p.path();
        if (s.substr(s.size() - 4, s.size()) != ".pdf")
            continue;

        Extractor ext(p.path());
        for (auto ref : ext)
            driver.writeEdge(ref);
    }

    fs::remove_all(temp_pdf_folder);
}

void Archive::download() {
    // cmd gives us the list of .tar files of pdfs to download 
    std::string cmd = "aws s3 cp --request-payer requester s3://arxiv/pdf/" + s3path + " " + s3path; 
    system(cmd.c_str());
}

void Archive::decompress() {
    if (!fs::exists(temp_pdf_folder))
        fs::create_directories(temp_pdf_folder);

    std::string cmd = "tar -xvf " + s3path + " -C " + temp_pdf_folder;
    system(cmd.c_str());
}
