#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>


class Author {
    public:
    std::string name;
};

class Paper {
    public:
    std::string id;
};

// from: first. to: second.
typedef std::pair<Paper, Paper> Reference;

// type of an edge between and author and a paper
typedef std::pair<Author, Paper> Edge;


template <class Hashable> class Bloom {
    public:
    Bloom(int size, int hashers);
    bool seen(Hashable info);
    bool add(Hashable info);
};


class References {
    /**
     * Object used to parse references from a paper's PDF.
     * 
     * A ``References`` object is given a ``Paper`` P and must create a list of
     * ``Paper``s which are referenced by P. It must call arxiv to download the
     * pdf associated to P, extract the text from this pdf and look for
     * reference string patterns.
     */

    private:
    /**
     * Private variables:
     *      - ``references``: holds parsed references.
     *      - ``textBuffer``: text of paper's pdf.
     */
    std::vector<Reference> references;
    std::stringstream textBuffer;

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
     * Called by libcurl when data is received. This function must convert
     * the pdf bytes to text incrementally (as the data arrives). This requires
     * some thought but is doable.
     *
     * The motivation behind this is that It is more efficient than waiting for
     * all the data before converting (look up non-blokcing IO).
     *
     * The text data must be stored in ``textBuffer``.
     */
    static std::size_t fillBuffer(
        void *contents,
        std::size_t size,
        std::size_t nmemb,
        std::stringstream *buf);  // buf will be a pointer to ``textBuffer``

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
    References(Paper paper);
};


class Crawler {
    /**
     * Arxiv crawler used to generate interaction data.
     * 
     * This is the main contribution of the data gathering team. An object of
     * this class is used to crawl arxiv for interaction data. It follows edges
     * between authors & papers. There is an edge between author A and paper P
     * if and only if:
     *      - author A is an author of paper P or
     *      - author A is an author of a paper referencing paper P
     * 
     * This definition is natural in the sense that the author must understand
     * the content of all papers he shares an edge with.
     */

    public:
    Crawler();

    /**
     * Facilitator function wrapping libcurl calls.
     * @param url full url (containing GET parameters) to fetch through libcurl
     * @return arxiv's response in a string
     */
    static std::string callArxiv(std::string url);

    /**
     * Crawl arxiv from author names.
     * @param authors a vector of author names.
     * @return a vector of (author, paper) pairs.
     */
    std::vector<Edge> fromAuthors(std::vector<Author> authors);

    /**
     * Crawl arxiv from paper identifiers.
     * @param papers a vector of paper identifiers.
     * @return a vector of (author, paper) pairs.
     */
    std::vector<Edge> fromPapers(std::vector<Paper> papers);

    class iterator : public std::iterator<
            std::input_iterator_tag,
            Edge, int, const Edge*, Edge> {
        /**
         * Iterator over interaction data.
         * 
         * A main part of ``Crawler``'s functionality is enclosed in this class.
         * It is as we iterate over interaction data that we generate it. The
         * data will be generated on demand. Only when we have no more will the
         * iterator make more requests to arxiv and parse responses.
         */

        private:
        /**
         * ``buffer`` holds data crawled by the parent crawler. ``cursor``
         * represents the position in the buffer of the iterator user. This
         * should always be at the beginning of the list as we will delete seen
         * data as we send it to the user.
         */
        std::list<Edge> buffer;
        std::list<Edge>::iterator cursor;

        public:
        // crawler is the parent crawler
        iterator(Crawler crawler);

        /**
         * Increment the ``cursor`` position.
         * 
         * If we need more data (our buffer is empty), we must call the parent
         * crawler.
         */
        iterator& operator++();
        iterator operator++(int);  // postfix version of above. no work here

        /**
         * For it != crawler.end()?
         * This is an infinite iterator and so there is no end condition.
         */
        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

        /**
         * @return value at our ``cursor``.
         */
        Edge operator*() const;
    };
};
