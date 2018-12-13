#include <string>
#include <vector>


class Crawler {
    public:
        /** vector storing all pairs found */
        std::vector<std::pair<std::string, std::string>> pairs;

        /** Facilitator function wrapping libcurl calls.
         * @param url full url (containing GET parameters) to fetch through libcurl
         * @return arxiv's response in a string
         */
        static std::string callArxiv(std::string url);

        /** Crawl arxiv from paper identifiers.
         * @param papers a vector of paper identifiers.
         * @return a vector of (author, paper) pairs.
         * 
         * For now this returns a vector. We should consider making it some form of
         * iterator.
         */
        std::vector<std::pair<std::string, std::string>> fromPapers(std::vector<std::string> papers);

        /** Crawl arxiv from author names.
         * @param authors a vector of author names.
         * @return a vector of (author, paper) pairs.
         * 
         * For now this returns a vector. We should consider making it some form of
         * iterator.
         */
        std::vector<std::pair<std::string, std::string>> fromAuthors(std::vector<std::string> authors);

        /** Crawl arxiv, alternating calls to ``fromPapers`` and ``fromAuthors``.
         * @param paper a source paper to start crawling from.
         * @param steps a number of steps to crawl for (counting calls).
         * 
         * Each (author, paper) pair is stored in ``this->pairs``.
         */
        void crawl(std::string paper, int steps);
};
