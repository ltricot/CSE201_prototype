#include "client.h"
#include <string>

Client::Client(std::string ip, int port) : ip(ip), port(port) {
}

std::vector<std::string> Client::getTopics(){
    std::vector<std::string> test_topics = {
        "physics", "math", "computers"
    };
    return test_topics;
}

std::vector<std::string> Client::getLikes(Author author){
    std::vector<std::string> test_string = {"physics", "math", "computers"};

    return test_string;
}

bool Client::putLikes(Author author, std::vector<std::string> topics){
    return true;
}

Paper Client::getRecommendation(Author author) {
    Paper test_paper("1812.01234");
    return test_paper;
}

std::vector<std::string> Client::getArticles(Author author){
    std::vector<std::string> test = {"1812.01234", "1901.03532", "1901.03680"};
    return test;
}

bool Client::putArticles(std::vector<std::string> articles){
    return true;
}

std::string Client::getTitle(Paper paper)
{
    return "Title test";
}
