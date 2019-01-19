#include "client.hpp"
#include "curl/curl.h"
#include "rapidxml/rapidxml.hpp"
#include "tools.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>

Client::Client(std::string ip, int port) : ip(ip), port(port) {
    topics = getTopics();
}

std::string encode(std::string name) {
    CURL *curl = curl_easy_init();
    char *encoded = curl_easy_escape(curl, name.c_str(), name.size());
    return encoded;
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
    std::string response = get(ip + "/users/" + encode(author.name) + "/likes");

    json resp = json::parse(response);
    std::vector<std::string> ret;
    for(std::string topic : topics) {
        int like = resp[topic];
        if(like == 1)
            ret.push_back(topic);
    }
    return ret;
}

bool Client::putLikes(Author author, std::vector<std::string> topics) {
    std::string body;
    json j;

    for (auto topic : this->topics) {
        if (std::find(topics.begin(), topics.end(), topic) != topics.end())
            j[topic] = 1;
        else
            j[topic] = 0;
    }
    body = j.dump();

    std::string response = put(ip + "/users/" + encode(author.name) + "/likes", body);
    json resp = json::parse(response);
    return resp["success"] == 1;
}

Paper Client::getRecommendation(Author author) {
    std::string response = get(ip + "/users/" + encode(author.name) + "/recommendation");
    json resp = json::parse(response);
    std::string id = resp["article"];
    return Paper(id);
}

std::vector<std::string> Client::getArticles(Author author) {

    std::string response = get(ip + "/users/" + encode(author.name) + "/articles");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
    return ret;
}

bool Client::putArticles(Author author, std::vector<std::string> articles) {
    json body;
    for (std::vector<std::string>::iterator it = articles.begin(); it != articles.end(); ++it) {
        body.push_back(*it);
    }

    std::string response = post(ip + "/users/" + encode(author.name) + "/articles", body);
    json resp = json::parse(response);
    return resp["success"] == 1;
}

std::string getTitle(Paper paper) {
    // return value
    std::string title;

    // getting the string containing html data
    std::string xmlstr;
    xmlstr = get("http://export.arxiv.org/api/query?id_list=" + paper.id);

    // "doc" is the XML tree
    rapidxml::xml_document<> doc;
    std::vector<char> xmlcharvec(xmlstr.begin(), xmlstr.end());
    xmlcharvec.push_back('\0');
    doc.parse<0>(&xmlcharvec[0]);

    // defining the root of XML tree
    rapidxml::xml_node<> *root = doc.first_node("feed");

    // getting the title
    title = root->first_node("entry")->first_node("title")->value();

    return title;
}