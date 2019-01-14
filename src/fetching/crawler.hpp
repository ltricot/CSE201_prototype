#include "references.hpp"
// #include "bloom.hpp"

#include <vector>
#include <list>


// url building facilities. relatively primitive but it should do
// as of now these are not used, the functions ``fromPapers`` and
// ``fromAuthors`` should be modified to use them.
static std::string papersUrl(std::vector<std::string> ids);
static std::string authorsUrl(std::vector<std::string> aus);
std::string getID(std::string link);


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

    private:

    bool from;  // when false: from authors. when true: from papers.
    Paper source;

    public:

    std::set<std::string> Set ; 

    // constructor
    Crawler(Paper source) : source(source) {}

    /**
     * Facilitator function wrapping libcurl calls.
     * 
     * @param url full url (containing GET parameters) to fetch through libcurl
     * @return arxiv's response in a string
     */
    static std::string callArxiv(std::string url);

    /**
     * Obtain (author, paper) pairs from an arxiv response.
     * 
     * @param xmlstr string of arxiv's response representing an xml structure.
     * @return a vector of edges
     */
    static std::vector<Edge> getPairs(std::string xmlstr);

    /**
     * Obtain a paper's abstract from an arxiv response.
     * 
     * @param xmlstr string of arxiv's response representing an xml structure.
     * @return a string of the paper's abstract
     */
    static std::vector<Paper> getSummary(std::string xmlstr);

    /**
     * Crawl arxiv from author names.
     * 
     * @param authors a vector of author names.
     * @return a vector of (author, paper) pairs.
     */
    std::vector<Edge> fromAuthors(std::vector<Author> authors);

    /**
     * Crawl arxiv from paper identifiers.
     * 
     * @param papers a vector of paper identifiers.
     * @return a vector of (author, paper) pairs.
     */
    std::vector<Edge> fromPapers(std::vector<Paper> papers);

    /**
     * Crawl for ``steps`` steps. If ``steps`` is negative, crawl forever.
     * This function will be called in a thread so as to work concurrently with
     * the uploads to the database.
     * 
     * We will move over the bloom & buffer checks currently done by the iterator
     * so as to not call arxiv uselessly.
     */
    std::vector<Edge> crawl(int steps);

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
        std::list<Edge>::iterator cursor;
        // Bloom<Edge> bloom;
        Crawler *crawler;

        public:
        std::list<Edge> buffer;
        // crawler is the parent crawler
        iterator(Crawler *crawler);

        /**
         * Increment the ``cursor`` position.
         * 
         * If we need more data (our buffer is empty), we must call the parent
         * crawler.
         */
        iterator operator++();
        // iterator operator++(int);  // postfix version of above. no work here

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

    iterator begin();
    iterator end();
};
