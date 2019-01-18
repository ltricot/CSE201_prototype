// @author Miha Smaka
#include <pistache/endpoint.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace Pistache;


int search_ns(int st, std::string &res){
	int ns;	
	for (int i = st; i < res.length(); i++) {
		ns = i;
		if (res[i] == '/') {
			break;
		}
	}
	return ns;
}


struct MyHandler: public Http::Handler {
    HTTP_PROTOTYPE(MyHandler)
	string dir;
    void onRequest(const Http::Request& request, Http::ResponseWriter writer) {
	//std::cout << request.resource() << std::endl;
	
	auto url_s = request.resource();
	auto bod = request.body();
	auto method = request.method();

	std::stringstream ss_url;
	std::stringstream ss_body;
	std::string body;
	std::string url;

	ss_url << url_s;
	url = ss_url.str();
	
	
	if (method == Http::Method::Get) {
		int fs = search_ns(2, url);
		//std::cout << fs << std::endl << url.length() << std::endl;
		if (fs == url.length()-1) {
			//std::string json = getTopics();
			//the above is for later
			std::string json = "{SEND NUDES}";
			writer.send(Http::Code::Ok, json);
			
		}


		else {
			int ns = search_ns(fs + 1, url);
			std::string ids = url.substr(fs + 1, ns - fs - 1);
			auto id = std::stoi(ids,nullptr);			
			//std::cout << id << std::endl;		
			std::string top = url.substr(ns + 1);
			
			std::string json = "test";	
			if (top == "likes") {
				//std::string json = getUserLikes(id);
				//the above is for later
			
				json = "{\"physics\" : 0, \"math\": 1, \"computers\": 1}";
				writer.send(Http::Code::Ok, json);
			}
			else if (top == "recommendation") {
				//std::string json = getUserReco(id);
				//the above is for later
				json = "{\"article\": \"1812.01234_v2\" }";
	
			}

			else if (top == "articles") {
				//std::string json = getUserArts(id);
				//the above is for later
				json = "{\"1812.01234_v2\", \"1609.43210\"}";
			}
			
				
			writer.send(Http::Code::Ok, json);

		}
	}

	else if (method == Http::Method::Put) {
		int fs = search_ns(0, url);
		int ns = search_ns(fs, url);
		std::string ids = url.substr(fs + 1, ns - fs - 1);
		//auto id = std::stoi(ids, nullptr);			
		std::string inson = request.body();
		//PARSE THE FUCKING JSON
		//putUserLikes(id, topics);
		
		std::string json = "{\"success\": 1}";
		
		writer.send(Http::Code::Ok, json);
	
	}

	else if (method == Http::Method::Post) {
		int fs = search_ns(0, url);
		int ns = search_ns(fs, url);
		std::string ids = url.substr(fs + 1, ns - fs - 1);
		//auto id = std::stoi(ids, nullptr);			
		std::string inson = request.body();
		//PARSE THE FUCKING JSON
		//putUserArticles(id, articles, dr);
		
		std::string json = "{\"success\": 1}";
		
		writer.send(Http::Code::Ok, json);
	}
	else {
		writer.send(Http::Code::Method_Not_Allowed);
	}
}
};

vector<string> getUserArticles(std::string id, std::string dr){
	Author u(id);
	Driver d(dr);
	vector<Edge> tmp = d.getFrom(u);
	vector<string> ret;
	for (vector<Edge>::iterator it = tmp.begin(); it != tmp.end(); it++){
		ret.push_back((it->paper).id);
	}
	return ret;
}
void putUserArticles(std::string id, std::vector<std::string> articles, std::string dr){
	Author u(id);
	Driver d(dr);
	for(std::vector<std::string>::iterator it = articles.begin(); it != articles.end(); it+++){
		bool b = d.writeEdge(Edge(u, Paper(*it)));
	}
}	

int main(int argc, char *argv[]) {
	std::ostringstream ostr;
	ostr << argv[1];
	std::string dir = ostr.str();
	Net::Address addr(Net::Ipv4::any(), Net::Port(80));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    server.serve();
}

