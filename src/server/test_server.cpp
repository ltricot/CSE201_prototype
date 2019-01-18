#include "client.hpp"
#include "driver.hpp"
#include <iostream>
#include <sstream>
#include <string>
}

// 40.89.156.133

void print_vect(std::vector<std::string> vect) {
    std::vector<std::string>::iterator it;
    for (it = vect.begin(); it != vect.end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main() {

    std::string ip = "40.89.156.133";
    Client::Client MyC(ip, 80);
    std::vector<std::string> tops = MyC.getTopics();
    Author testy = "Testy McTestface";
    std::vector<std::string> getliks = MyC.getLikes(testy);
    std::vectore<std::string> topics;
    topics.push_back("SEND NUDES");
    topics.push_back("PLEASE");
    topics.push_back("I AM DESPERATE");
    bool sucliks = MyC.putLikes(testy, topics);

    Paper SUCCC = MyC.getRecommendation(testy);

    std::vector<std::string> arts = MyC.getArticles(testy);

    print_vect(tops);

    return 0;
}

// sudo g++-7 test.cpp -lpistache -pthread -std=c++11