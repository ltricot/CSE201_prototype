#include "primitives.hpp"
// #include "bloom.hpp"

#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include <set>
#include <pair>

#include <curl/curl.h>


/** @brief get references for a vector of papers
 * 
 * @details this function reads from the `references` object.
 * 
 * @param papers vector of paper objects from which we wish to extract references
 * @return pairs of papers ; for each pair, the first references the second
 */
std::vector<std::pair<Paper, Paper>> getReferences(std::vector<Paper>);

std::map<std::string, std::vector<std::string>>
setUpReferences(std::string folder, std::vector<std::string> archives);

void writeFile(std::map<std::string, std::vector<std::string>> data, std::string filename);
void readFile(std::string filename);


class References {
    /**
     * Object used to parse references from a paper's PDF.
     * 
     * A ``References`` object is given a ``Paper`` P and its PDF text and must
     * create a list of ``References``s associated to P. It must execute pattern
     * search algorithms to find said references.
     */

    private:

    // simple internal alias
    typedef std::pair<Paper, Paper> Reference;

    /**
     * Private variables:
     *      - ``references``: holds parsed references.
     *      - ``textBuffer``: text of paper's pdf.
     */
    std::vector<Reference> references;
    const std::string textBuffer;
    const Paper paper ; 

    public:
    /**
     * Iterator functionality.
     * Simple delegation to the underlying ``references`` vector. Give this no
     * thought when developing this object, only when using it.
     */
    typedef std::vector<Reference>::iterator iterator;
    iterator begin() { return this->references.begin(); }
    iterator end() { return this->references.end(); }

    /**
     * Assuming ``textBuffer`` has been completely filled, get all arxiv
     * references and store them in ``references``.
     */
    void getReferences();

    /**
     * The constructor ensures that the object may be iterated over and
     * immediately yield all found references in ``paper``.
     */
    References(Paper paper, std::string text);
};


class PDF : public std::string {
    public:

    PDF(std::string str) {
        *this = str;
    }
};

class PDFConverter {
    private:
    // where we store the pdf input & text output
    std::stringstream pdfBuffer;
    std::stringstream textBuffer;

    public:
    CURL *handle;

    // constructor that takes as input a pdf file and stores the result in pdfBuffer
    PDFConverter(PDF pdf);

    // constructor that launches the curl_easy_setopt for the pdf with the provided id, and stores the result in pdfBuffer
    PDFConverter(std::string id);

    // convenience constructor for testing purposes
    PDFConverter(std::stringstream *pdf); // PDFConverter(std::string pdf);

    /**
     * Called by libcurl when data is received. We will not be converting the pdf
     * to text incrementally because this requires incremental decompression using
     * zlib and that's annoying.
     *
     * The text data must be stored in ``textBuffer``.
     */
    static std::size_t fillBuffer(
        char *contents,
        std::size_t size,
        std::size_t nmemb,
        std::stringstream *buf);  // buf will be a pointer to ``textBuffer``

    // apply conversion once pdf is downloaded
    std::string getText();
};

class Papers {
    /**
     * Manages the download of paper pdf's and constructs the necessary
     * information from the results. Necessary as we will make concurrent
     * requests to arxiv.
     * 
     * Given a vector of paper IDs, construct for each paper:
     *  - a references object
     *  - a PDFConverter object
     * 
     * With this information the ``Crawler`` object can build edges easily and
     * the TF-IDF component can build its frequency matrices.
     */

    private:
    const std::vector<std::string> ids;

    // in-object convenience
    std::vector<Paper> papers;
    std::vector<std::pair<Paper, Paper>> references;

    // curl multi handle
    CURLM *mhandle; // maybe should be public like for thr PDFConverter class?

    // curl stuff - you may change this structure as you will
    int *stillRunning;
    void initialize();
    void perform();
    void cleanup();  // should be idempotent

    public:

    /** All the work should be done here. To make the use of this object simple,
     * when this constructor returns, the ``edges`` attributed should be
     * finalized.
     * 
     * For each id in ids, create a PDFConverter object.
     * Manage those with a curl multi handle and launch all downloads. Using the
     * ``select`` functionality, notice when each download finishes and immediately
     * call the associated PDFConverter's ``getText`` method to convert the pdf to text.
     * 
     * For every pdf converted to text this way, construct a ``References`` object
     * which will be responsible for reference pattern matching.
     */
    Papers(std::vector<std::string> ids);

    /** We need a second Papers constructor, which takes as argument the PDF files directly
     * no need to do a curl request 
     */
    Papers(std::vector<std::string> ids, std::vector<PDF> pdfs);

    std::vector<std::pair<Paper, Paper>> getReferences();
};


class BulkDownloader {
    /** Second PDF downloader component,
     * doesn't choose the pdfs downloaded, but much faster.
     * 
     * Downloads the pdfs from S3, somewhere where 
     * arxiv stores data massively.
     * 
     * Necessary because arxiv blocks us after the 
     * download of ~1000 pdfs using the first method
     * over a small time period.
     * 
     * As soon as we have the pdf, we want to store
     * the references in it.
     * 
     * Our crawler will then upload them once it 
     * "discovers" the article.  
     * 
     */

    private:

    std::string which;
    std::string folder;      // name of the folder into which the files will be downloaded

    public:

    void downloadTar();        // downloads a file .tar.gz and stores it in the folder `folder`
    void decompress();         // decompress the file
    Papers constructPapers();    // opens each pdf downloaded and creates a Papers object, then deletes each pdf file

    BulkDownloader(std::string which, std::string folder)
        : which(which), folder(folder) {}

};
