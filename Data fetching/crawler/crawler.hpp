#include "primitives.hpp"
#include <vector>
#include <list>


// url building facilities. relatively primitive but it should do
static std::string papersUrl(std::vector<std::string> ids);
static std::string authorsUrl(std::vector<std::string> aus);


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
