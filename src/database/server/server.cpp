#include <pistache/endpoint.h>
#include <iostream>
using namespace Pistache;

struct HelloHandler : public Http::Handler {
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter writer) {
        writer.send(Http::Code::Ok, request.body(), MIME(Text, Plain));
	std::cout << request.body() << std::endl;
    }
};

int main() {
    Http::listenAndServe<HelloHandler>("*:80");
}
