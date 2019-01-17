#include "client.hpp"
#include "crawler.hpp"
#include "tools.hpp"

#include <iostream>
#include <string>
#include <vector>

Client::Client(std::string ip, int port) : ip(ip), port(port) { 
    std::vector<std::string> topics = getTopics(); 
}

std::vector<std::string> Client::getTopics() {
    std::string response = get(ip + "/topics");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
    return ret;
}

std::vector<std::string> Client::getLikes(Author author) {
    std::string response = get(ip + "/users/" + author.name + "/likes");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
    return ret;
}

bool Client::putLikes(Author author, std::vector<std::string> topics) {
    std::string body;
    json j;
    
    for(auto topic : this->topics){
        if(std::find(topics.begin(), topics.end(), topic) != topics.end())
            j[topic] = 1;
        else
            j[topic] = 0;
    }
    body = j.dump();

    std::string response = put(ip + "/users" + author.name + "likes");
    json resp = json::parse(response);
    if (resp["success"] == 1)
        return true;
    else
        return false;
}

Paper Client::getRecommendation(Author author) {
    std::string response = get(ip + "/users/" + author.name + "/recommendation");
    json resp = json::parse(response);
    std::string id = resp["article"];
    return Paper(id);
}

Paper Client::getSummary(Paper paper) {
    std::string xmlstr;
    std::vector<Paper> summaries;
    xmlstr = get("http://export.arxiv.org/api/query?id_list=" + paper.id);
    summaries = Crawler::getSummary(xmlstr);
    for(std::vector<Paper>::iterator it = summaries.begin(); it != summaries.end(); ++it) {
        if(it->id == paper.id)
            return *it;
    }

    std::cout << "Call the cops" << std::endl;
    exit(EXIT_FAILURE);
}

std::vector<std::string> Client::getArticles(Author author) {

    std::string response = get(ip + "/users/" + author.name + "/articles");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
}

//the following functions is not finished yet
bool Client::putArticles(std::vector<std::string> articles) {
    std::string response = post(ip + "/users/", articles[0]);
    json resp = json::parse(response);
    return resp["success"] == 1;
}