#include <string>

#include "json.hpp"
#include "primitives.hpp"


using json = nlohmann::json;


class Client {
    public:

    // server properties
    std::string ip;
    int port;

    Client(std::string ip, int port);

    std::vector<std::string> getTopics();
    std::vector<std::string> getLikes(Author author);
    bool putLikes(Author author, std::vector<std::string>);
    Paper getRecommendation(Author author);
    std::vector<std::string> getArticles(Author author);
    bool putArticles(std::vector<std::string> articles);
}
