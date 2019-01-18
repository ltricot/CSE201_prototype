// @author Miha Smaka
#include <pistache/endpoint.h>
#include <iostream>
#include <string>
#include <sstream>
#include "../database/driver.hpp"
#include <fstream>

using namespace Pistache;


using json = nlohmann::json;



class GUI_Serv {

    GUI_Serv(std::string d, Address addr){
        httpEndpoint(std::make_shared<Http::Endpoint(addr));
        dir = d;
    }
	std::string dir;

	Rest::Router router;

	void setupRouter() {
		using namespace Rest;
		Routes::Get(router, "/topics", Routes::bind(&getTopics, this));
		Routes::Get(router, "/users/:id/likes", Routes::bind(&getLikes, this));
		Routes::Get(router, "/users/:id/recommendation", Routes::bind(&getReco, this));
		Routes::Get(router, "/users/:id/articles", Routes::bind(&getArticles, this));
		Routes::Put(router, "/users/:id/likes", Routes::bind(&putLikes, this));
		Routes::Post(router, "/users/:id/articles", Routes::bind(&postArts, this));
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
        httpEndpoint->shutdown();
    }

	std::string js;

	void getTopics(const Rest::Request& request, Http::ResponseWriter response) {
		js = "{SEND NUDES}";
		response.send(Http::Code::Ok, js);
	}

	void getLikes(const Rest::Request& request, Http::ResponseWriter response) {
		auto id = request.param(":id").as<int>;
		std::string likes = getUserLikes(id)
		//js = "{\"physics\" : 0, \"math\": 1, \"computers\": 1}"; //answer for testing response
		response.send(Http::Code::Ok, js);
	}

	void getReco(const Rest::Request& request, Http::ResponseWriter response) {
		auto id = request.param(":id").as<int>;
		//js = getUserRecs(id)
		js = "{\"article\": \"1812.01234_v2\" }";
		response.send(Http::Code::Ok, js);
	}

	void getArts(const Rest::Request& request, Http::ResponseWriter response) {
		auto id = request.param(":id").as<std::string>;
		std::vector<std::string> articles = getUserArticles(id, dir);
		articles.push_back("1812.01234_v2"); //these two construct a manual response
		articles.push_back("1609.43210"); //for testing purposes
		if (articles.empty()) {
			response.send(Http::Code::No_Content, "The user does not exist.")
			return;
		}
		js = jsonize(articles);
		response.send(Http::Code::Ok, js);
	}

	void putLikes(const Rest::Request& request, Http::ResponseWriter response) {
		auto id = request.param(":id").as<std::string>;
		auto bod = request.body();
		std::stringstream ss_body;
		ss_body << bod;
		std::string data = ss_body.str();
		json d = json::parse(data);
		std::vector<std::string> out;
		for (json::iterator it = d.begin(); it != d.start(); it++){
			out.push_back(*it);
		}
		bool succ = putUserLikes(id, out);
		if (succ) {
			response.send(Http::Code::Ok, "{\"success\": 1}");
			return;
		}
		else{
			response.send(Http::Code::Not_Found, "{\"failure\": 0}" )
			return;
		}
		response.send(Http::Code::Ok, "{\"success\": 1}");
	}

	void postArts(const Rest::Request& request, Http::ResponseWriter response) {
		auto id = request.param(":id").as<std::string>;
		auto bod = request.body();
		std::stringstream ss_body;
		ss_body << bod;
		std::string data = ss_body.str();
		json d = json::parse(data);
		std::vector<std::string> out;
		for (json::iterator it = d.begin(); it != d.start(); it++){
			out.push_back(*it);
		}
		bool suc = putUserArticles(id, out, dir);
		if (suc) {
			response.send(Http::Code::Ok, "{\"success\": 1}");
			return;
		}
		else{
			response.send(Http::Code::Not_Found, "{\"failure\": 0}" )
			return;
	}
	
};
std::vector<std::string> getU
bool putUserLikes(std::string id, std::vector<std::string> likes){
	for(std::vector<std::string>::iterator it = likes.begin(); it != likes.end(); it++){
		bool b = putUserLike(id, *it);
	}
	return true;
}
bool putUserLike(std::string id, std::string like){
	std::string filename = id + ".txt";
	ifstream inp(filepath);
	ofstream out(id  + "tmp.txt");

	string line;
	bool liked = false;
	while (getline(inp, line)) {
			vector<string> vec;
			boost::algorithm::split(vec, line, boost::is_any_of(","));
			if (vec[0] == like) {
				out << line << "\n";
				liked = true;
			}
			else {
				out << line << "\n";
			}
		}
	}
	inp.close();

	if (liked) {
		out.close();
		remove(filepath.c_str());
		rename((id + "tmp.txt").c_str(), filepath.c_str());
		return true;
	}

	out << like << "\n";
	out.close();
	remove(filepath.c_str());
	rename((id + "tmp.txt").c_str(), filepath.c_str());
	return true;
}

std::string jsonize(std::vector<std::string>& arts) {
	std::string output = "{";
	std::vector<std::string>::iterator it;
	for (it = arts.begin(); it != arts.end(); it++) {
		std::string add = "\"" + *it  "\"";
		output += add + ",";
	}
	output += "}";
	return output;
}

std::vector<std::string> getUserArticles(std::string id, std::string dr){
	Author u(id);
	Driver d(dr);
	vector<Edge> tmp = d.getFrom(u);
	vector<string> ret;
	for (vector<Edge>::iterator it = tmp.begin(); it != tmp.end(); it++){
		ret.push_back((it->paper).id);
	}
	return ret;
}

bool putUserArticles(std::string id, std::vector<std::string> articles, std::string dr){
	Author u(id);
	Driver d(dr);
	for(std::vector<std::string>::iterator it = articles.begin(); it != articles.end(); it+++){
		bool b = d.writeEdge(Edge(u, Paper(*it)));
	}
	return true;
}



std::string urlDec(string &str){
	//credit to stackoverflow 
	//https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
    std::string out;
    char c;
    int f, sec
	int l = str.length();

    for (i=0; i < l; i++){
        if(str[i] != '%'){
            if(str[i] == '+')
                out += ' ';
            else
                out += str[i];
        }else{
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            c = static_cast<char>(ii);
            out += ch;
            i = i + 2;
        }
    }
    return ret;
}

int main(int argc, char** argv) {
	std::ostringstream ostr;
	ostr << argv[1];
	std::string dir = ostr.str();
	
	Address addr(Ipv4::any(), Port(80));
    GUI_Serv serv(dir, addr);

    serv.init();
    serv.start();
}