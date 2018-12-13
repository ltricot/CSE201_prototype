#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>

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
    /*TO DO:
    - port it to personal github and make a general implementation
        - add the formulas for calculating n, k, m, p and describe it well
    - finish the docs below
    - start coding!!!
    */
    /*
    * Data structure that allows us to check membership (and insert) in less than linear time.
    *
    * It is made as a template as the only assumption made on the type of information stored 
    * in the Bloom filter is that one can hash it efficiently. The below public methods are made
    * for all who simply wish to interact with the data structure, while not being bothered by
    * the details of it. 
    */   
    public:
    /*
    * Public variables:
    *       
    * Public methods:
    *       - ``Bloom(std::string path, int bitsize)``: simply a constructor, it is subject to change when I start coding.
    *    
    *       - ``bool seen(Hashable info)``: returns False if the ``Hashable info` is not in the Bloom filter, 
    *           and returns True if it is.
    *       - ``bool add(Hashable info)``: adds the `Hashable info`` to the Bloom filter.
    *       - ``void reset()``: as the name suggest it resets the Bloom filter to an empty state - this will not 
    *           delete any saved files just clears the filter in the C++ (i.e. re-initializes it)
    *           ATTENTION - THIS IS NOT A DESTRUCTOR
    *       - ``Bloom * import(std::string path)``: reads an existing Bloom filter structure from a data file located at 
    *           the ``std::string path`` and returns it as a pointer to a ``Bloom`` object.
    *       - ``void export(std::string path)``: exports the Bloom object to a ``.dat`` file located at the ``std::string path``    
    *           location.
    *       - ``void setPath(std::string path)``: a standard setter method for the path location.
    *       - ``std::string getPath()``: a standard getter method for the path variable.
    *       - ``~Bloom()``: your standard destructor class that takes care of deallocating memory.
    */
    Bloom(std::string path, int bitsize);
    Bloom(std::string path);
    Bloom(int bitsize);
    Bloom();
    bool seen(Hashable info);
    bool add(Hashable info);
    void reset();
    Bloom * import(std::string path);
    void export(std::string path);
    void setPath(std::string path);
    std::string getPath();
    ~Bloom();
    std::string DoYouHash; 
    //NOTE: THE PRIVATE PART IS UNFINISHED AND SUBJECT TO CHANGE
    private:
    /*
    * Private variables:
    *       - ``std::string path``: stores the path (absolute) location of where the Bloom filter (byteset should be stored.     
    *           The value defaults to NULL if it is not provided in the constructor.
    *       - ``int hashers``: the amount of hash functions used, initialized in this project to 23.
    *       - ``bset``: the current bitset that stores the Bloom filter. The number of bits was calculated by
    *           https://hur.st/bloomfilter/
    *       - ``int bitsize``: sets the size of the biteset that will be used to store the filter. For this project leave it
    *           empty to have it done for you.
    *       
    * Private methods:
    *       - ``int[hashers] * hash(Hashable info)``: returns array containing the hashes of the (Hashable info) computed by
    *          the ``hashers`` different hash functions. Basically will tell us what bits to set in the bitset.
    *       - ``int[hashers] getBits(std::vector<unsigned long int>  locs)``: returns a pointer to an array of bits (1s and 0s) 
    *           located in ``bset`` at the locations specified in ``locs``.
    *       - ``void setBits(std::vector<unsigned long int> locs)``: sets the bits located in ``bset``
    *           at the locations specified in ``locs`` to 1. We only support setting to 1 as that is 
    *           all we need in a Bloom filter.
    */
    std::string path;
    int hashers;
    int bitsize;
    std::bitset bset(bitsize);
    
    int[hashers] * hash(Hashable info);
    int[hashers] * getBits(std::vector<unsigned long int>  locs);
    void setBits(std::vector<unsigned long int> locs);
    
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
