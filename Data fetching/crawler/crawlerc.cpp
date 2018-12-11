#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "rapidxml-1.13/rapidxml.hpp"
#include <curl/curl.h>

#include "crawlerc.hpp"


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

std::string Crawler::callArxiv(std::string url) {
    CURL *curl_handle;
    CURLcode res;

    std::string response;

    // initialize curl session
    // curl_gloabl_init shoyuld be outside of this method
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

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

static std::vector<std::pair<std::string, std::string>>
getPairs(std::string xmlstr) {
    // return value
    std::vector<std::pair<std::string, std::string>> pairs;

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
            pairs.push_back(std::make_pair(name, article));
        }
    }

    std::cout << "oh dang" << std::endl;
    return pairs;
}

std::vector<std::pair<std::string, std::string>>
Crawler::fromAuthors(std::vector<std::string> authors) {
    // return value & auxiliary iteration variable
    std::vector<std::pair<std::string, std::string>> pairs;
    std::vector<std::pair<std::string, std::string>> pairs_aux;

    // initialize iteration variables
    std::vector<std::string>::iterator author;
    std::ostringstream url;  // for url building
    std::string xmlstr;

    // each iteration is one call to arxiv*
    // it is likely that we should have some waiting period between each call
    // so as not to be blocked by arxiv (they are a small organization)
    for(author = authors.begin(); author != authors.end(); author++) {
        url.str("");
        url << "http://export.arxiv.org/api/query?search_query=au:" << *author;
        xmlstr = this->callArxiv(url.str());

        // extend found pairs with this authors new pairs
        pairs_aux = getPairs(xmlstr);
        pairs.reserve(pairs.size() + distance(pairs_aux.begin(), pairs_aux.end()));
        pairs.insert(pairs.end(), pairs_aux.begin(), pairs_aux.end());
    }

    return pairs;
}
