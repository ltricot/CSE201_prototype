#include "primitives.hpp"

#include <vector>
#include <memory>
#include <sstream>
#include <map>


class References {
    /**
     * Object used to parse references from a paper's PDF.
     * 
     * A ``References`` object is given a ``Paper`` P and its PDF text and must
     * create a list of ``References``s associated to P. It must execute pattern
     * search algoritms to find said references.
     */

    private:
    /**
     * Private variables:
     *      - ``references``: holds parsed references.
     *      - ``textBuffer``: text of paper's pdf.
     */
    std::vector<Reference> references;
    const std::string textBuffer;

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
     * Constructor.
     * 
     * Must call arxiv to download the pdf and convert it to text through
     * ``fillBuffer``. Once this process is over, the constructor must call
     * ``getReferences`` to fill up the ``references`` vector.
     * 
     * The constructor ensures that the object may be iterated over and
     * immediately yield all found references in ``paper``.
     */
    References(Paper paper, std::string pdf) : textBuffer(pdf) {}
};


class PDFConverter {
    private:
    // where we store the pdf input & text output
    std::stringstream pdfBuffer;
    std::stringstream textBuffer;

    public:
    PDFConverter();

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
     *  - a summary object
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

    // curl stuff
    void initialize();
    void perform();
    void cleanup();  // should be idem potent


    public:
    std::vector<Edge> edges;

    /**
     * All the work should be done here. To make the use of this object simple,
     * when this constructor returns, the ``edges`` attributed should be
     * finalized.
     */
    Papers(std::vector<std::string> ids) : ids(ids) {}
};
