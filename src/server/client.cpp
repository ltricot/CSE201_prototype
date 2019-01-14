#include "client.hpp"
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
    Paper test_paper("1812.01234_v2");
    return test_paper;
}

Paper Client::getSummary(Paper paper) {
    paper.summary = R"(Consumer electronic (CE) devices increasingly rely on wireless local area
networks (WLANs). Next generation WLANs will continue to exploit multiple
antenna systems to satisfy the growing need for WLAN system capacity.
Multiple-input multiple-output (MIMO) antenna systems improve the spectral
efficiency and single user throughput. Multi-user MIMO (MU-MIMO) systems
exploit the spatial separation of users for increasing the sum-throughput. In
an MU-MIMO system, efficient channel sounding is essential for achieving
optimal performance. The system analysis in this paper provides insights into
the rate at which to perform channel sounding. This paper shows that optimal
sounding intervals exist for single user transmit beamforming (SU-TxBF) and
MU-MIMO, and proposes a low-complexity dynamic sounding approach for practical
MU-MIMO WLAN deployments. The proposed approach adjusts the sounding interval
adaptively based on the real-time learning outcomes in the given radio
environment. Using real over-the-air channel measurements, significant
throughput improvements (up to 31.8%) are demonstrated by adopting the proposed
dynamic sounding approach, which is compliant with IEEE 802.11ac.)";
    return paper;
}

std::vector<std::string> Client::getArticles(Author author){
    std::vector<std::string> test = {"1812.01234_v2", "1901.03532", "1901.03680"};
    return test;
}

bool Client::putArticles(std::vector<std::string> articles){
    return true;
}
