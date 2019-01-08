#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

#include "rapidxml/rapidxml.hpp"
#include <curl/curl.h>

#include "crawler.hpp"
#include "bloom.cpp"

/** ``writefunction`` parameter of a curl call
 * 
 * @param contents pointer to data received by curl
 * @param size size of each member of ``contents``
 * @param nmemb number of members of ``contents``
 * @param s pointer to string inside which we store all received data
 * 
 * comments:
 *  - we may optimize this with a stringstream for ``s`` which makes resizing
 *    natural
 */
static std::size_t makeString(void *contents, size_t size, size_t nmemb, std::string *s) {
    std::size_t newLength = size * nmemb;
    std::size_t oldLength = s->size();

    try {
        s->resize(oldLength + newLength);
    } catch(std::bad_alloc &error) {
        // handle memory problem
        return 0;
    }

    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}

// useless as of now, but necessary else g++ throws an undefined reference error
Crawler::Crawler() {}

std::string Crawler::callArxiv(std::string url) {
    CURL *curl_handle;
    CURLcode res;

    std::string response;

    // initialize curl session
    // curl_gloabl_init shoyuld be outside of this method
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);  // ugh so much printing

    // provide the URL to use in the request
    // we must esacpe the url (get rid of bad characters)
    // const char* c_url = url.c_str();
    // char* escaped = curl_easy_escape(curl_handle, c_url, 0);

    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);     // very useful for libcurl and/or protocol debugging and understanding
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);  // tells the library to shut off the progress meter completely for requests done with this handle

    // send all data to this callback function
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, makeString);

    // data pointer to pass to the write callback
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    // perform the request, res will get the return code 
    res = curl_easy_perform(curl_handle);

    // cleanup curl stuff  
    // curl_free(escaped);
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return response;
}

std::vector<Edge> Crawler::getPairs(std::string xmlstr) {
    // return value
    std::vector<Edge> pairs;

    /* We initialize here a number of variable used when traversing the
     * XML tree.
     * - ``xmlstr`` is the string containing xml data
     * - ``doc`` is the XML tree
     * - ``root`` is essentially the XML tree's root
     * - ``entry`` and ``author`` are XML tree nodes, and are our iteration variables
     * - ``article`` and ``name`` are the values we wish to return
     */
    rapidxml::xml_document<> doc;
    std::vector<char> xmlcharvec(xmlstr.begin(), xmlstr.end());
    xmlcharvec.push_back('\0');
    doc.parse<0>(&xmlcharvec[0]);

    rapidxml::xml_node<> *root = doc.first_node("feed"),
        *entry,
        *author;

    std::string name, article;

    // iteration over entries (representing articles)
    for(entry = root->first_node("entry");
            entry && entry->name() == std::string("entry");
            entry = entry->next_sibling()) {
        article = entry->first_node("id")->value();

        // iteration over authors of this article
        for(author = entry->first_node("author");
                author && author->name() == std::string("author");
                author = author->next_sibling()) {
            name = author->first_node("name")->value();

            pairs.push_back(Edge(Author(name), Paper(article)));
        }
    }

    return pairs;
}

std::vector<Edge>
Crawler::fromAuthors(std::vector<Author> authors) {
    // return value & auxiliary iteration variable
    std::vector<Edge> pairs;
    std::vector<Edge> pairs_aux;

    // initialize iteration variables
    std::vector<Author>::iterator author;
    std::ostringstream url;  // for url building
    std::string xmlstr;

    // each iteration is one call to arxiv
    // it is likely that we should have some waiting period between each call
    // so as not to be blocked by arxiv (they are a small organization)
    for(author = authors.begin(); author != authors.end(); author++) {
        url.str(""); url << "http://export.arxiv.org/api/query?search_query=au:";
        url << author->name << "&maxresults=100";
        xmlstr = this->callArxiv(url.str());

        // extend found pairs with this author's new pairs
        pairs_aux = getPairs(xmlstr);
        pairs.reserve(pairs.size() + distance(pairs_aux.begin(), pairs_aux.end()));
        pairs.insert(pairs.end(), pairs_aux.begin(), pairs_aux.end());
    }

    return pairs;
}

std::vector<Edge>
Crawler::fromPapers(std::vector<Paper> papers) {
    // return value & auxiliary iteration variable
    std::vector<Edge> pairs;
    std::vector<Edge> pairs_aux;

    // initialize iteration variables
    std::vector<Paper>::iterator article;
    std::ostringstream url;  // for url building
    std::string xmlstr;

    // each iteration is one call to arxiv*
    // it is likely that we should have some waiting period between each call
    // so as not to be blocked by arxiv (they are a small organization)
    for(article = papers.begin(); article < papers.end(); article += 15) {
        url.str(""); url << "http://export.arxiv.org/api/query?id_list=";
        for(std::vector<Paper>::iterator art = article;
                art < min(papers.end(), article + 30); art++) {
            url << article->id << ',';
        } url << "&maxresults=30";

        xmlstr = this->callArxiv(url.str());

        // extend found pairs with this article's new pairs
        pairs_aux = getPairs(xmlstr);
        pairs.reserve(pairs.size() + distance(pairs_aux.begin(), pairs_aux.end()));
        pairs.insert(pairs.end(), pairs_aux.begin(), pairs_aux.end());
    }

    return pairs;
}

// id of paper from link to paper on arxiv
std::string getID(std::string link) {
    std::string temp;
    std::stringstream link_s(link);
    while(std::getline(link_s, temp, '/'));
    return temp;
}



Crawler::iterator::iterator(Crawler crawler) {
    this->parent = crawler;
}

bool Crawler::iterator::operator==(iterator other) const {
    return false;
}

bool Crawler::iterator::operator!=(iterator other) const {
    return true;
}
/**
 * @return an Edge
 */
Edge Crawler::iterator::operator*() const {
    return *cursor;
}

iterator& Crawler::iterator::operator++() {
    /* @brief implementation of the incrementation operator of the cursor iterator.
     * @details the buffer is the place where we store the Edges fetched by the crawler.
     * The while loop checks two conditions: 
     *      1) if the Edge pointed by the cursor is already in the bloom (it was seen)
     *      2) and if the cursor is not already at the end of the buffer
     * then we have to increment again the iterator i.e. go to the next Edge.
     * 
     * otherwise, if the current Edge was not seen in the buffer, we add it to the buffer
     * and if the cursor is at the end of the buffer, we have to empty it and call the crawler to fetch new Edges
     * which we will put in the buffer.
     */
    while (bloom.seen(*cursor) && cursor != buffer.end()) {
        cursor++();
    }

    if (!bloom.seen(*cursor)) {
        bloom.add(Hashable info);
    }
    if (cursor == buffer.end()) {
        std::vector<Edge> edges = parent.crawl();
        for (Edge edge : edges) {
            buffer.push_back(edge)
        }
    }
}

std::vector<Paper> Crawler::getSummary(std::string xmlstr) {
    // return value
    std::vector<Paper> summ;
    
    /* We initialize here a number of variable used when traversing the
     * XML tree.
     * - ``xmlstr`` is the string containing xml data
     * - ``doc`` is the XML tree
     * - ``root`` is essentially the XML tree's root
     * - ``entry`` are XML tree nodes, and are our iteration variables
     * - ``article`` and ``summary` are the values we wish to return
     */
    rapidxml::xml_document<> doc;
    std::vector<char> xmlcharvec(xmlstr.begin(), xmlstr.end());
    xmlcharvec.push_back('\0');
    doc.parse<0>(&xmlcharvec[0]);
    
    rapidxml::xml_node<> *root = doc.first_node("feed"),
    *entry,
    
    std::string summary, article;
    
    // iteration over entries (representing articles)
    for(entry = root->first_node("entry");
        entry && entry->name() == std::string("entry");
        entry = entry->next_sibling()) {
        article = entry->first_node("id")->value();
        summary = entry->first_node("summary")->value();

        summ.push_back(Paper(article, summary));
        
    }
    
    return summ;
}