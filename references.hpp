#include "primitives.hpp"

#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include <curl/curl.h>


class References {
    /**
     * Object used to parse references from a paper's PDF.
     * 
     * A ``References`` object is given a ``Paper`` P and its PDF text and must
     * create a list of ``References``s associated to P. It must execute pattern
     * search algorithms to find said references.
     */

    private:
    /**
     * Private variables:
     *      - ``references``: holds parsed references.
     *      - ``textBuffer``: text of paper's pdf.
     */
    std::vector<References> references;
    const std::string textBuffer;

    public:
    /**
     * Iterator functionality.
     * Simple delegation to the underlying ``references`` vector. Give this no
     * thought when developing this object, only when using it.
     */
    typedef std::vector<References>::iterator iterator;
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
    References(Paper paper, std::string text) : textBuffer(text) {}
};


class PDFConverter {
    private:
    // where we store the pdf input & text output
    std::stringstream pdfBuffer;
    std::stringstream textBuffer;

    public:
    const CURL *handle;

    // constructor that takes as input a pdf file and stores the result in pdfBuffer
    PDFConverter(PDF pdf) {} 

    // constructor that launches the curl_easy_setopt for the pdf with the provided id, and stores the result in pdfBuffer
    PDFConverter(std::string *id) {}

    // convenience constructor for testing purposes
    PDFConverter(std::stringstream *pdf);

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
    std::map<std::string, Paper> papers;
    std::map<Paper, std::shared_ptr<References>> references;

    // pdf conversion objects
    std::map<Paper, std::shared_ptr<PDFConverter>> PDFConverters;

    // curl multi handle
    CURLM *mhandle; // maybe should be public like for thr PDFConverter class?

    // curl stuff - you may change this structure as you will
    void initialize();
    void perform();
    void cleanup();  // should be idem potent

    int *stillRunning ; 

    public:
    std::vector<Edge> edges;

    /**
     * All the work should be done here. To make the use of this object simple,
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
    Papers(std::vector<std::string> ids) : ids(ids) {}

    /**
     * We need a second Papers constructor, which takes as argument the PDF files directly
     * no need to do a curl request 
    */
    Papers(PDF pdf) {}
};




class BulkDownloader()  {
    /**
     * Second PDF downloader component,
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
    string folder = pdfs ;      // name of the folder into which the files will be downloaded 
    void downloadTar() ;        // downloads a file .tar.gz and stores it in the folder "./pdfs"
    void decompress() ;         // decompress the file 
    void constructPapers() ;    // opens each pdf downloaded and creates a Papers object, then deletes each pdf file
                                // idk how to make it delete the whole folder at the end ? 
    void destroy();             // deletes the folder 



}; 