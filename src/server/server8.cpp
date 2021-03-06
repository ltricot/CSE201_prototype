// @author Miha Smaka
#include "driver.hpp"
#include "Reader.h"
#include "json.hpp"
#include "declaration_knn.hpp"

#include "pistache/endpoint.h"
#include "pistache/http.h"
#include "pistache/router.h"

#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace Pistache;

using json = nlohmann::json;


/** @brief Returns the user's liked topics
 *
 * @details Finds the user's text file and returns the topics it contains in the form of a
 * vector of strings
 *
 * @param id the User's id
 *
 * @return vector of topics
 */
std::vector<std::string> getUserLikes(std::string id, std::string dr) {
    Reader r(dr + "/" +id + ".txt");
    std::vector<std::vector<std::string>> tmp = r.read();
    std::vector<std::string> ret;
    for(auto it : tmp) {
        ret.push_back(it[0]);
    }
    return ret;
}

/**@brief Records the fact that the user liked this topic
 *
* @details Creates or opens a text file with the user's id, then adds the like
*
* @param id the User's id
*
* @param like a topic liked by the user
*/
bool putUserLike(std::string id, std::string like, std::string dr) {
    std::string filename = dr + "/" + id + ".txt";
    ifstream inp(filename);
    ofstream out(id + "tmp.txt");

    string line;
    bool liked = false;
        while (getline(inp, line)) {
            if (line == like) {
                out << line << "\n";
                liked = true;
            } else {
                out << line << "\n";
            }
        }
    inp.close();
    if (liked) {
        out.close();
        remove(filename.c_str());
        rename((id + "tmp.txt").c_str(), filename.c_str());
        return true;
    }

    out << like << "\n";
    out.close();
    remove(filename.c_str());
    rename((id + "tmp.txt").c_str(), filename.c_str());
    return true;
}

/**@brief Calls putUserLike(id, like) on each like in likes
 */
bool putUserLikes(std::string id, std::vector<std::string> likes, std::string dr) {
    for (auto it : likes)
        bool b = putUserLike(id, it, dr);
    return true;
}

/**@brief Recovers the articles that the user liked.
 *
 * @details Goes into the interaction matrix and returns the row corresponding to the user's id
 *
 * @param id The user's id
 *
 * @param dr The directory of the interaction matrix
 *
 * @return A vector containing the ids of the papers associated to the user
 */
std::vector<std::string> getUserArticles(std::string id, std::string dr) {
    Author u(id);
    Driver d(dr);
    vector<Edge> tmp = d.getFrom(u);
    vector<string> ret;
    for (vector<Edge>::iterator it = tmp.begin(); it != tmp.end(); it++) {
        ret.push_back((it->paper).id);
    }
    return ret;
}

/** @brief Records the fact that the user liked these articles
 *
 * @details Adds an edge in the interaction matrix between the user and every papaper
 *
 * @param id the User's id
 *
 * @param articles Vector of articles
 *
 * @param dr The interaction matrix's directory
 */
bool putUserArticles(std::string id, std::vector<std::string> articles, std::string dr) {
    Author u(id);
    Driver d(dr);
    for (std::vector<std::string>::iterator it = articles.begin(); it != articles.end(); it++) {
        bool b = d.writeEdge(Edge(u, Paper(*it)));
    }
    return true;
}

std::string decodeUrl(std::string nameEnc) {
    CURL *curl = curl_easy_init();
    int cp;
    char *decoded = curl_easy_unescape(curl, nameEnc.c_str(), nameEnc.size(), &cp);
    std::string ret(decoded, decoded + cp);
    curl_free(decoded);
    curl_easy_cleanup(curl);
    return ret;
}

std::string jsonize(std::vector<std::string> &arts) {
    std::string output = "[";
    std::vector<std::string>::iterator it;
    for (it = arts.begin(); it != arts.end(); it++) {
        std::string add = "\"" + *it + "\"";
        output += add + ",";
    }
    output = output.substr(0, output.length()-1);
    output += "]";
    return output;
}

class GUI_Serv {
  public:
    std::string dir, user_dir, cldata, vdata;
    Rest::Router router;
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    std::vector<std::string> topics;

    GUI_Serv(std::string d, std::string d2, std::string cldata, std::string vdata, Address addr)
        : dir(d), user_dir(d2), cldata(cldata), vdata(vdata) {
        GUI_Serv::httpEndpoint = std::make_shared<Http::Endpoint>(addr);
        int res = mkdir(d2.c_str(), 0666);
        ifstream inp("topics.json");
        json j = json::parse(inp);
        this->topics = j.get<std::vector<std::string>>();
    }

    void setupRouter() {
        using namespace Rest;
        Routes::Get(router, "/topics", Routes::bind(&GUI_Serv::getTopics, this));
        Routes::Get(router, "/users/:id/likes", Routes::bind(&GUI_Serv::getLikes, this));
        Routes::Get(router, "/users/:id/recommendation", Routes::bind(&GUI_Serv::getReco, this));
        Routes::Get(router, "/users/:id/articles", Routes::bind(&GUI_Serv::getArts, this));
        Routes::Put(router, "/users/:id/likes", Routes::bind(&GUI_Serv::putLikes, this));
        Routes::Put(router, "/users/:id/articles", Routes::bind(&GUI_Serv::putArts, this));
    }

    void init() {
        auto opts = Http::Endpoint::options().threads(1);
        setupRouter();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }

    void shutdown() {
        std::cout << "y u stop :(((((" << std::endl;
        httpEndpoint->shutdown();
    }

    std::string js;

  private:
    void getTopics(const Rest::Request &request, Http::ResponseWriter response) {
        json j = topics;
        GUI_Serv::js = j.dump();
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getLikes(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = (std::string) request.param(":id").as<std::string>();
        std::vector<std::string> ret = getUserLikes(id, user_dir);

        json j;
        if (ret.empty()) {
            response.send(Http::Code::Ok, "{}");
        }
        for (auto top : topics)
            if(std::find(ret.begin(), ret.end(), top) != ret.end())
                j[top] = 1;
            else
                j[top] = 0;

        std::string js = j.dump();
        GUI_Serv::js = js;
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getReco(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = decodeUrl((std::string) request.param(":id").as<std::string>());

        std::cout << "recommend: " << id << std::endl;
        json resp;

        std::cout << id << " " << dir << " " << cldata << " " << vdata << std::endl;
        Person person(Author(id), dir, cldata, vdata);
        resp["article"] = person.getRecommendation(10);

        std::cout << resp["article"] << std::endl;

        std::string js = resp.dump();
        GUI_Serv::js = js;
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getArts(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = (std::string)request.param(":id").as<std::string>();
        std::vector<std::string> articles = getUserArticles((std::string)id, GUI_Serv::dir);
        if (articles.empty()) {
            response.send(Http::Code::Ok, "[]");
            return;
        } 
        json s = articles;
        GUI_Serv::js = s.dump();
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void putLikes(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = (std::string)request.param(":id").as<std::string>();
        auto bod = request.body();
        std::stringstream ss_body;
        ss_body << bod;
        std::string data = ss_body.str();
        json d = json::parse(data);
        std::vector<std::string> out;

        for (auto el : d.items()) {
            if (el.value() == 1) {
                out.push_back(el.key());
            }
        }

        bool suc =  putUserLikes(id, out, user_dir);

        if (suc) {
            response.send(Http::Code::Ok, "{\"success\": 1}");

        } else {
            response.send(Http::Code::Not_Found, "{\"failure\": 0}");
    
        }
    }

    void putArts(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = (std::string)request.param(":id").as<std::string>();
        auto bod = request.body();
        std::stringstream ss_body;
        ss_body << bod;
        std::string data = ss_body.str();
        json d = json::parse(data);
        std::vector<std::string> out;
        json::iterator it;
        for (it = d.begin(); it != d.end(); it++) {
            out.push_back(*it);
        }
        bool suc = putUserArticles((std::string)id, out, GUI_Serv::dir);
        if (suc) {
            response.send(Http::Code::Ok, "{\"success\": 1}");
    
        } else {
            response.send(Http::Code::Not_Found, "{\"failure\": 0}");
    
        }
    }
};

int main(int argc, char **argv) {
    
    std::string cdata = argv[1];
    std::string userdir = argv[2];  // for topic likes
    std::string cldata = argv[3];
    std::string vdata = argv[4];

    Address addr(Ipv4::any(), Port(80));
    GUI_Serv serv(cdata, userdir, cldata, vdata, addr);

    serv.init();
    serv.start();
}
