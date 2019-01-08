#include <iostream>
#include "crawler.hpp"


int main(int argc, char *argv[]) {
    Crawler crawler;

    for (auto edge : crawler) {
        std::cout << edge.paper.id << std::endl;
    }
}
