#include <iostream>
#include "client.hpp"


int main() {
    std::cout << "Hello World" << std::endl;

    Author Shakespeare("Shakespeare");
    Client Tom("20.188.35.105", 80);
    Paper Bestpaper("1901.05944");

    std::vector<std::string> topics = Tom.getTopics();
    for (auto i = topics.begin(); i != topics.end(); ++i)
        std::cout << *i << ' ';

    std::vector<std::string> likes = Tom.getLikes(Shakespeare);
    for (auto i = likes.begin(); i != likes.end(); ++i)
        std::cout << *i << ' ';

    std::vector<std::string> articles = Tom.getArticles(Shakespeare);
    for (auto i = articles.begin(); i != articles.end(); ++i)
        std::cout << *i << ' ';

    bool outcome = Tom.putArticles(Shakespeare, {"1901.05944"});
    std::cout << outcome << std::endl;

    bool outcome2 = Tom.putLikes(Shakespeare, {"physics", "math", "computers"});
    std::cout << outcome2 << std::endl;

    Paper paper = Tom.getRecommendation(Shakespeare);
    std::cout << paper.id << std::endl;

    // Paper paper2 = Tom.getSummary(Bestpaper);
    // std::cout<< paper2.id << std::endl;

    return 0;
}
