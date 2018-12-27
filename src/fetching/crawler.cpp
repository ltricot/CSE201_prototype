#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

#include "rapidxml-1.13/rapidxml.hpp"
#include <curl/curl.h>

#include "crawler.hpp"
#include "bloom.cpp"


Crawler::iterator::iterator(Crawler crawler) {
    this->parent = crawler;
}

bool Crawler::iterator::operator==(iterator other) const {
    return false;
}

bool Crawler::iterator::operator!=(iterator other) const {
    return true;
}

Edge Crawler::iterator::operator*() const {
    return *cursor;
}

iterator& Crawler::iterator::operator++() {
    /* implementation of the incrementation operator of the cursor iterator.
     * the buffer is the place where we store the Edges fetched by the crawler.
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

