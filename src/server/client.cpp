#include "client.hpp"
#include "tools.hpp"

#include <vector>
#include <string>


Client::Client(std::string ip, int port) : ip(ip), port(port) {
    topics = getTopics();
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

bool Client::putLikes(Author author, std::vector<std::string> topics) {
    std::string body;

    json j;
    for(auto topic : this->topics) {
        if(std::find(topics.begin(), topics.end(), topic) != topics.end())
            j[topic] = 1;
        else
            j[topic] = 0;
    }
    body = j.dump();

    std::string response =  put(ip + "/users/" + author.name + "/likes", body);
    json resp = json::parse(response);

    if (resp["success"] == 1)
        return true;
    else
        return false;
}

Paper Client::getRecommendation(Author author) {
    std::string response = get(ip + /users/:id/recommendation);
    json resp = json::parse(response);
    Paper new_paper(resp.article);
    return new_paper;
}

Paper Client::getSummary(Paper paper) {
    std::string = response get(ip + /);
}

std::vector<std::string> Client::getArticles(Author author) {
     
    std::string response = get(ip + "/users/:id/articles");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for(json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
}

bool Client::putArticles(std::vector<std::string> topics) {
    std::string body;

    
    std::string response =  post(ip + "/users/" + author.name + "/articles", body);
    json resp = json::parse(response);

    if (resp["success"] == 1)
        return true;
    else
        return false;
}
}
