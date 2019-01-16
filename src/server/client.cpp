#include "client.hpp"
#include "tools.cpp"

#include <vector>
#include <string>


Client::Client(std::string ip, int port) : ip(ip), port(port) {
}

std::vector<std::string> Client::getTopics(){
    std::string response = get(ip + "/topics");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for(json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
}

std::vector<std::string> Client::getLikes(Author author) {
    return get(ip + /users/:id/likes);
}

bool Client::putLikes(Author author, std::vector<std::string> topics){
    return post(ip + /users/:id/likes);
}

Paper Client::getRecommendation(Author author) {
    return get(ip + /users/:id/recommendation);
}

Paper Client::getSummary(Paper paper) {
    return get(ip + /);
}

std::vector<std::string> Client::getArticles(Author author){
    return get(ip + /users/:id/articles);
}

bool Client::putArticles(std::vector<std::string> articles){
    return post(ip + /users/:id/articles)
}
