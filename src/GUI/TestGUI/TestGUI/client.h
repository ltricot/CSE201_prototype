#ifndef CLIENT_H
#define CLIENT_H
#pragma once
#include <string>

#include "json.h"
#include "primitives.h"


using json = nlohmann::json;


class Client {
    public:

    // server properties
    std::string ip;
    int port;

    Client(std::string ip, int port);

    std::vector<std::string> getTopics();
    std::vector<std::string> getLikes(Author author);
    bool putLikes(Author author, std::vector<std::string> topics);
    Paper getRecommendation(Author author);
    std::vector<std::string> getArticles(Author author);
    bool putArticles(std::vector<std::string> articles);
    std::string getTitle(Paper paper);
};

#endif // CLIENT_H
