#include <curl/curl.h>
#include <fstream>
#include <map>
#include <iostream>
#include <stdio.h>

/** ``writefunction`` parameter of a curl call
 * 
 * @param contents pointer to data received by curl
 * @param size size of each member of ``contents``
 * @param nmemb number of members of ``contents``
 * @param s pointer to string inside which we store all received data
 * 
 * comments:
 *  - we may optimize this with a stringstream for ``s`` which makes resizing
 *    natural
 */
static std::size_t makeString(void *contents, size_t size, size_t nmemb, std::string *s) {
    std::size_t newLength = size * nmemb;
    std::size_t oldLength = s->size();

    try {
        s->resize(oldLength + newLength);
    } catch(std::bad_alloc &error) {
        // handle memory problem
        return 0;
    }

    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}

std::string get(std::string url) {
    //creating curl object
    CURL *curl;
    std::string response;

    //initializing the curl object
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    // we must esacpe the url (get rid of bad characters)
    const char* c_url = url.c_str();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
    // send all data to this callback function so we can return it afterwards
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, makeString);

    // data pointer to pass to the write callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // perform the request
    curl_easy_perform(curl);

    //cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    //error handling
    if (response.size() == 0){
        return "curl_easy_perform() failed";
    }
    return response;
}

// as for now I don't do anything with fields map (std::map<std::string, std::string> fields)
// not finished
void post(std::string url, std::string body){
    //size of our data we want to send
    int size = body.size();

    //creating curl object
    CURL *curl;

    //initializing the curl object
    curl = curl_easy_init();
    
    // we must esacpe the url (get rid of bad characters)
    const char* c_url = url.c_str();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
    //-------------------
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, size);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &body);
    //-------------------

    // perform the request
    curl_easy_perform(curl);
}

// g++ simpl.cpp -lcurl
// ./a.out

int main() {
    std::string response;
    response = get("http://www.example.com");
    std::cout << response << std::endl;
    return 0; 
}
