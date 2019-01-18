#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

#include "rapidxml/rapidxml.hpp"
#include <curl/curl.h>

#include "crawler.hpp"
#include "driver.hpp"


// id of paper from link to paper on arxiv
std::string getID(std::string link) {
    std::string temp;
    std::stringstream link_s(link);
    while (std::getline(link_s, temp, '/'))
        ;
    return temp;
}

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
    } catch (std::bad_alloc &error) {
        // handle memory problem
        return 0;
    }

    std::copy((char *)contents, (char *)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}

std::string Crawler::callArxiv(std::string url) {
    CURL *curl_handle;
    CURLcode res;

    std::string response;

    // initialize curl session
    // curl_gloabl_init shoyuld be outside of this method

    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L); // ugh so much printing

    // provide the URL to use in the request
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE,
                     0L); // very useful for libcurl and/or protocol debugging
                          // and understanding
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS,
                     1L); // tells the library to shut off the progress meter
                          // completely for requests done with this handle

    // send all data to this callback function
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, makeString);

    // data pointer to pass to the write callback
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    // perform the request, res will get the return code
    res = curl_easy_perform(curl_handle);

    // cleanup curl stuff
    // curl_free(escaped);
    curl_easy_cleanup(curl_handle);
    return response;
}


std::vector<Edge> Crawler::getPairs(std::string xmlstr) {
    std::cerr << "Crawler::getPairs" << std::endl;

    // return value
    std::vector<Edge> pairs;

    /* We initialize here a number of variable used when traversing the
     * XML tree.
     * - ``xmlstr`` is the string containing xml data
     * - ``doc`` is the XML tree
     * - ``root`` is essentially the XML tree's root
     * - ``entry`` and ``author`` are XML tree nodes, and are our iteration
     * variables
     * - ``article`` and ``name`` are the values we wish to return
     */
    rapidxml::xml_document<> doc;
    std::vector<char> xmlcharvec(xmlstr.begin(), xmlstr.end());
    xmlcharvec.push_back('\0');
    doc.parse<0>(&xmlcharvec[0]);

    rapidxml::xml_node<> *root = doc.first_node("feed"), *entry, *author;

    std::string name, article;

    // iteration over entries (representing articles)
    int i = 0;
    for (entry = root->first_node("entry"); entry && entry->name() == std::string("entry");
         entry = entry->next_sibling()) {
        article = getID(entry->first_node("id")->value());

        // Paper(article) has to be created here with the summary 
        std::vector<Paper> summary = getSummary(xmlstr);
        Paper paper = summary[i];

        if(paper.id != article) {
            std::cerr << "Call the cops" << std::endl;
            std::cerr << paper.id << " != " << article << std::endl;
            exit(EXIT_FAILURE);
        }

        // iteration over authors of this article
        for (author = entry->first_node("author");
             author && author->name() == std::string("author"); author = author->next_sibling()) {
            name = author->first_node("name")->value();
            pairs.push_back(Edge(Author(name), paper));
        }

        i++; // means we're getting the next paper
    }

    std::cerr << "pairs.size(): " << pairs.size() << std::endl;
    return pairs;
}


std::vector<Edge> Crawler::fromAuthors(std::vector<Author> authors) {
    std::cerr << "Crawler::fromAuthors" << std::endl;
    for(auto a : authors)
        std::cerr << a.name << std::endl;

    // return value & auxiliary iteration variable
    std::vector<Edge> pairs;
    std::vector<Edge> pairs_aux;

    // initialize iteration variables
    std::vector<Author>::iterator author;
    std::ostringstream url; // for url building
    std::string xmlstr;

    // each iteration is one call to arxiv
    // it is likely that we should have some waiting period between each call
    // so as not to be blocked by arxiv (they are a small organization)

    for (author = authors.begin(); author < authors.end(); author += 15) {
        url.str("");
        url << "http://export.arxiv.org/api/query?search_query=";

        for(auto a = author ; a < min(authors.end(), author +15 ); a++, url << "+OR+"){
            char *escaped = curl_escape(a->name.c_str(), a->name.length());
            url << "au:" << escaped ; 
            curl_free(escaped);
        }

        xmlstr = this->callArxiv(url.str());


        // extend found pairs with this author's new pairs
        pairs_aux = getPairs(xmlstr);
        pairs.reserve(pairs.size() + distance(pairs_aux.begin(), pairs_aux.end()));
        pairs.insert(pairs.end(), pairs_aux.begin(), pairs_aux.end());
    }

    return pairs;
}

std::vector<Edge> Crawler::fromPapers(std::vector<Paper> papers) {
    std::cerr << "Crawler::fromPapers" << std::endl;
    for(auto p : papers)
        std::cerr << p.id << std::endl;

    // return value & auxiliary iteration variable
    std::vector<Edge> pairs;
    std::vector<Edge> pairs_aux;

    // initialize iteration variables
    std::vector<Paper>::iterator article;
    std::ostringstream url; // for url building
    std::string xmlstr;

    // each iteration is one call to arxiv*
    // it is likely that we should have some waiting period between each call
    // so as not to be blocked by arxiv (they are a small organization)
    for (article = papers.begin(); article < papers.end(); article += 15) {
        url.str("");
        url << "http://export.arxiv.org/api/query?id_list=";
        for (std::vector<Paper>::iterator art = article; art < min(papers.end(), article + 15);
             art++) {
            url << article->id << ',';
        }
        url << "&maxresults=30";

        xmlstr = this->callArxiv(url.str());

        // extend found pairs with this article's new pairs
        pairs_aux = getPairs(xmlstr);
        pairs.reserve(pairs.size() + distance(pairs_aux.begin(), pairs_aux.end()));
        pairs.insert(pairs.end(), pairs_aux.begin(), pairs_aux.end());
    }

    return pairs;
}

// Crawler::iterator::iterator(Crawler *crawler) { this->parent = crawler; }

bool Crawler::iterator::operator==(iterator other) const { return false; }

bool Crawler::iterator::operator!=(iterator other) const { return true; }

/**
 * @return an Edge
 */
Edge Crawler::iterator::operator*() const {
    std::cerr << "Crawler::iterator::operator*" << std::endl;

    auto ret = *cursor;
    return ret;
}

Crawler::iterator::iterator(Crawler *crawler, bool init) : crawler(crawler) {
    if (init) {  // crawl a bit at initialization
        std::vector<Edge> edges = crawler->crawl(2);
        for (Edge edge : edges)
            buffer.push_back(edge);
    }

    cursor = buffer.begin();
}

Crawler::iterator Crawler::iterator::operator++() {
    /* @brief implementation of the incrementation operator of the cursor
     * iterator.
     * @details the buffer is the place where we store the Edges fetched by the
     * crawler. The while loop checks two conditions: 1) if the Edge pointed by
     * the cursor is already in the Set (it was seen) 2) and if the cursor is
     * not already at the end of the buffer then we have to increment again the
     * iterator i.e. go to the next Edge.
     *
     * otherwise, if the current Edge was not seen in the buffer, we add it to
     * the buffer and if the cursor is at the end of the buffer, we have to
     * empty it and call the crawler to fetch new Edges which we will put in the
     * buffer.
     */

    // while (bloom.seen(*cursor) && cursor != buffer.end())
    // while (crawler->Set.find(cursor) != crawler->Set.end() && cursor != buffer.end()) {
    //     cursor++;
    // }
    std::cerr << "Crawler::iterator::operator++" << std::endl;

    if (cursor == buffer.end())
        goto fillup;
    else if (++cursor == buffer.end())
        goto fillup;
    else
        goto done;

    fillup: {
        buffer.clear();
        std::vector<Edge> edges = crawler->crawl(1);
        for (Edge edge : edges) {
            buffer.push_back(edge);
        }

        cursor = buffer.begin();
    }

    // auto edge = *(*this);

    // if (!bloom.seen(edge))
    // if (crawler.Set.find(edge) == crawler->Set.end()) {
    //     bloom.add(edge);
    // }

    done:
    return *this ; 

}

Crawler::iterator Crawler::begin() {
    iterator it(this, true);
    return it;
}

Crawler::iterator Crawler::end() {
    iterator it(this);
    return it;
}

std::vector<Paper> Crawler::getSummary(std::string xmlstr) {
    std::cerr << "Crawler::getSummary" << std::endl;

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

    rapidxml::xml_node<> *root = doc.first_node("feed"), *entry;

    std::string summary, article;

    // iteration over entries (representing articles)
    for (entry = root->first_node("entry"); entry && entry->name() == std::string("entry");
         entry = entry->next_sibling()) {
        //article = entry->first_node("id")->value();
        article = getID(entry->first_node("id")->value()); 
        summary = entry->first_node("summary")->value();

        summ.push_back(Paper(article, summary));
    }

    return summ;
}

/** @brief Functions that takes care of the crawling.
 *
 * @details
 * @params steps the number of times we'll repeat the process
 * @params from if set to 1 comes from papers, if set to 0
 * comes from authors
 *
 * @return a vector of (author, paper) pairs.
 */
std::vector<Edge> Crawler::crawl(int steps) {
    std::cerr << "Crawler::crawl" << std::endl;
    Driver driver(this->refdata);
    Driver d(this->cdata);

    std::vector<Edge> buffer;
    std::vector<Edge> tempPapers;
    std::vector<Edge> tempAuthors;

    while (steps-- > 0) {
        // beug
        // Paper last;

        // case where from = 1, i.e. request comes from papers
        // then, we call fromPapers()
        if (from) {
            /* FIND WHICH PAPERS TO FOLLOW THROUGH */
            std::vector<Paper> start = paperSource; // vector of one Paper with value source
            std::vector<Paper> unseen; // vector of Paper objects not already in
                                       // the Set (i.e. we haven't seen them)

            for (std::vector<Paper>::iterator paper = start.begin(); paper != start.end();
                 paper++) {

                if (Set.find(paper->id) == Set.end()) {
                    unseen.push_back(*paper);
                    Set.insert(paper->id);
                }
            }
            /* END FIND */

            /* FOLLOW UNSEEN PAPERS */
            tempPapers = fromPapers(unseen);

            // we get the references of the papers we havent already seen

            std::vector<Reference> references ;

            //std::vector<Paper> papers;
            for (std::vector<Edge>::iterator edge = tempPapers.begin(); edge != tempPapers.end();
                 edge++) {
                //papers.push_back(edge->paper);

                std::vector<Reference> refs = driver.getFrom(edge->paper) ;

                for(std::vector<Reference>::iterator ref = refs.begin(); ref != refs.end();
                 ref++) {
                     references.push_back(*ref) ;
                }
            }
          
            // before : std::vector<Reference> references = getReferences(papers);



            std::vector<Edge> newEdges;
            
            for (int i = 0; i != references.size(); i++) {

                if (buffer[i].paper.id == references[i].first.id) {
                    // we add this edge only if we havent seen the author nor
                    // the paper


                    if (Set.find(buffer[i].author.name) == Set.end() &&
                        Set.find(references[i].second.id) == Set.end()) {

                        newEdges.push_back(Edge(buffer[i].author, references[i].second));

                        std::cerr << Edge(buffer[i].author, references[i].second).paper.id << std::endl ; 
                    }
                }
            }
            

            // Move elements from newEdges to tempPapers.
            tempPapers.insert(tempPapers.end(), std::make_move_iterator(newEdges.begin()),
                              std::make_move_iterator(newEdges.end()));

            // Move elements from tempPapers to buffer.
            buffer.insert(buffer.end(), tempPapers.begin(), tempPapers.end());

            // set author source for next iter
            authorSource.clear();
            for(auto edge : tempPapers)
                authorSource.push_back(edge.author);

            // beug
            // last = tempPapers.end()->paper ; 

            // add things to Set
        } else {
            std::vector<Author> authors;
            for (std::vector<Author>::iterator author = authorSource.begin(); author != authorSource.end();
                 author++) {

                // if we havent seen this author we take it
                if (Set.find(author->name) == Set.end()) {
                    authors.push_back(*author);
                    Set.insert(author->name);

                    // beug
                    // last = edge->paper.id ; 
                }
            }

            tempAuthors = fromAuthors(authors);

            paperSource.clear();
            for(auto edge : tempAuthors)
                paperSource.push_back(edge.paper);

            // Move elements from tempAuthors to buffer.
            buffer.insert(buffer.end(), std::make_move_iterator(tempAuthors.begin()),
                          std::make_move_iterator(tempAuthors.end()));
            
        }

        this->from = !(this->from);
    }

    std::cerr << "buffer.size(): " << buffer.size() << std::endl;
    return buffer;
}

void Crawler::run() {
    Driver d(cdata);
    SummaryAccessor ds(sdata);
    for(auto edge = this->begin();; ++edge) {
        Edge ed = *edge;
        d.writeEdge(ed);
        ds.sendSummary(ed.paper);
    }
}
