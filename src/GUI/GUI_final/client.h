#ifndef CLIENT_H
#define CLIENT_H
#include <string>

#include "json.h"
#include "primitives.h"


using json = nlohmann::json;


// trivial

class Client {
    private:
    std::vector<std::string> topics;
    public:

    // server properties
    std::string ip;
    int port;

    Client(std::string ip, int port);

    std::vector<std::string> getTopics();
    std::vector<std::string> getLikes(Author author);
    std::string getTitle(Paper paper);
    bool putLikes(Author author, std::vector<std::string> topics);
    Paper getRecommendation(Author author);
    std::vector<std::string> getArticles(Author author);
    bool putArticles(Author author, std::vector<std::string> articles);

    Paper getSummary(Paper paper);
};

#endif // CLIENT_H
