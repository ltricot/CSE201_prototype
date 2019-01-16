#include "client.hpp"
#include "crawler.hpp"
#include "tools.hpp"

#include <string>
#include <vector>

Client::Client(std::string ip, int port) : ip(ip), port(port) {}

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
    std::string response = get(ip + "/users/:id/likes");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
    return ret;
}

<<<<<<< HEAD
bool Client::putLikes(Author author, std::vector<std::string> topics) {
    std::string response = post(ip + "/users/:id/likes");
=======
bool Client::putLikes(Author author, std::vector<std::string> topics){
    std::string response =  put(ip + /users/:id/likes);
>>>>>>> db5f0d1dca23fc440382c12b58dce566cd7e0c7e
    json resp = json::parse(response);
    if (resp.success == 1) {
        return true
    } else {
        return false
    }
}

Paper Client::getRecommendation(Author author) {
<<<<<<< HEAD
    std::string response = get(ip + / users / : id / recommendation);
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
=======
    std::string response = get(ip + /users/:id/recommendation);
    json resp = json::parse(response);
    Paper new_paper(resp.article);
    return new_paper;
}

Paper Client::getSummary(Paper paper) {
    std::string = response get(ip + /);
>>>>>>> db5f0d1dca23fc440382c12b58dce566cd7e0c7e
}

std::vector<std::string> Client::getArticles(Author author) {

    std::string response = get(ip + "/users/:id/articles");
    json resp = json::parse(response);

    std::vector<std::string> ret;
    for (json::iterator it = resp.begin(); it != resp.end(); it++) {
        ret.push_back(*it);
    }
}

bool Client::putArticles(std::vector<std::string> articles) {
    std::string response = post(ip + / users / : id / articles) json resp = json::parse(response);
    if (resp.success == 1) {
        return true
    } else {
        return false
    }
}
