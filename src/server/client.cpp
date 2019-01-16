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
    return ret;
}

std::vector<std::string> Client::getLikes(Author author) {
    std::string response = get(ip + "/users/:id/likes");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for(json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
    return ret;
}

bool Client::putLikes(Author author, std::vector<std::string> topics){
    std::string response =  post(ip + /users/:id/likes);
    json resp = json::parse(response);
    if (resp.success == 1) {
        return true
    }
    else {
        return false
    }
}

Paper Client::getRecommendation(Author author) {
    std::string response = get(ip + /users/:id/recommendation);

}

Paper Client::getSummary(Paper paper) {
    return get(ip + /);
}

std::vector<std::string> Client::getArticles(Author author) {
     
    std::string response = get(ip + "/users/:id/articles");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for(json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
}

bool Client::putArticles(std::vector<std::string> articles){
    std::string response = post(ip + /users/:id/articles)
    json resp = json::parse(response);
    if (resp.success == 1) {
        return true
    }
    else {
        return false
    }
}

// hello world