// @author Miha Smaka
#include "../database/driver.hpp"
#include "json.hpp"
#include <iostream>
#include "pistache/endpoint.h"
#include "pistache/http.h"
#include "pistache/router.h"
#include <sstream>
#include <string>

using namespace Pistache;

using json = nlohmann::json;

std::string jsonize(std::vector<std::string> &arts) {
    std::string output = "{";
    std::vector<std::string>::iterator it;
    for (it = arts.begin(); it != arts.end(); it++) {
        std::string add = "\"" + *it + "\"";
        output += add + ",";
    }
    output += "}";
    return output;
}

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
bool putUserArticles(std::string id, std::vector<std::string> articles, std::string dr) {
    Author u(id);
    Driver d(dr);
    for (std::vector<std::string>::iterator it = articles.begin(); it != articles.end(); it++) {
        bool b = d.writeEdge(Edge(u, Paper(*it)));
    }
    return true;
}

class GUI_Serv {
  public:
    std::string dir;
    Rest::Router router;
    std::shared_ptr<Http::Endpoint> httpEndpoint;

    GUI_Serv(std::string d, Address addr) {
        GUI_Serv::httpEndpoint = std::make_shared<Http::Endpoint>(addr);
        dir = d;
    }

    void setupRouter() {
        using namespace Rest;
        Routes::Get(router, "/topics", Routes::bind(&GUI_Serv::getTopics, this));
        Routes::Get(router, "/users/:id/likes", Routes::bind(&GUI_Serv::getLikes, this));
        Routes::Get(router, "/users/:id/recommendation", Routes::bind(&GUI_Serv::getReco, this));
        Routes::Get(router, "/users/:id/articles", Routes::bind(&GUI_Serv::getArts, this));
        Routes::Put(router, "/users/:id/likes", Routes::bind(&GUI_Serv::putLikes, this));
        Routes::Post(router, "/users/:id/articles", Routes::bind(&GUI_Serv::postArts, this));
    }

    void init() {
        auto opts = Http::Endpoint::options().threads(1);
        setupRouter();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }

    void shutdown() { httpEndpoint->shutdown(); }

    std::string js;

  private:
    void getTopics(const Rest::Request &request, Http::ResponseWriter response) {
        GUI_Serv::js = "[\"physics\", \"math\", \"computers\"]";
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getLikes(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<std::string>();
        // js = getUserLikes(id)
        GUI_Serv::js =
            "{\"physics\" : 0, \"math\": 1, \"computers\": 1}"; // answer for testing response
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getReco(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<std::string>();
        // js = getUserRecs(id)
        GUI_Serv::js = "{\"article\": \"1812.01234_v2\"}";
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void getArts(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<std::string>();
        std::vector<std::string> articles = getUserArticles((std::string)id, GUI_Serv::dir);
        articles.push_back("1812.01234_v2"); // these two construct a manual response
        articles.push_back("1609.43210");    // for testing purposes
        if (articles.empty()) {
            response.send(Http::Code::No_Content, "The user does not exist.");
            return;
        }
        GUI_Serv::js = jsonize(articles);
        response.send(Http::Code::Ok, GUI_Serv::js);
    }

    void putLikes(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<std::string>();
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
        /*TO BE IMPLEMENTED
        bool suc = putUserLikes(id, out, dir);
        if (suc) {
                response.send(Http::Code::Ok, "{\"success\": 1}");
                return;
        }
        else{
                response.send(Http::Code::Not_Found, "{\"failure\": 0}" )
                return;
        }*/
        response.send(Http::Code::Ok, "{\"success\": 1}");
    }

    void postArts(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<std::string>();
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
            return;
        } else {
            response.send(Http::Code::Not_Found, "{\"failure\": 0}");
            return;
        }
    }
};

std::string urlDec(string &str) {
    // credit to stackoverflow
    // https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
    std::string out;
    char c;
    int f, sec;
    int l = str.length();

    for (int i = 0; i < l; i++) {
        if (str[i] != '%') {
            if (str[i] == '+')
                out += ' ';
            else
                out += str[i];
        } else {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &i);
            c = static_cast<char>(i);
            out += c;
            i = i + 2;
        }
    }
    return out;
}

int main(int argc, char **argv) {
    std::ostringstream ostr;
    ostr << argv[1];
    std::string dir = ostr.str();

    Address addr(Ipv4::any(), Port(80));
    GUI_Serv serv(dir, addr);

    serv.init();
    serv.start();
}