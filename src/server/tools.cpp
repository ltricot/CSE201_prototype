#include "tools.hpp"
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>

static std::size_t makeString(void *contents, size_t size, size_t nmemb, std::string *s) {
    std::size_t newLength = size * nmemb;
    std::size_t oldLength = s->size();

    try {
        s->resize(oldLength + newLength);
    } catch (std::bad_alloc &error) {
        // handle memory problem
        return 0;
    }

    std::copy((char *)contents, (char *)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}

struct To_send {
    const char *readptr;
    size_t sizeleft;
};

static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp) {
    struct To_send *data = (struct To_send *)userp;
    size_t buffer_size = size * nmemb;

    if (data->sizeleft) {
        // copy as much as possible from the source to the destination
        size_t copy_this_much = data->sizeleft;
        if (copy_this_much > buffer_size)
            copy_this_much = buffer_size;
        memcpy(dest, data->readptr, copy_this_much);

        data->readptr += copy_this_much;
        data->sizeleft -= copy_this_much;
        return copy_this_much;
    }

    return 0;
}

std::string get(std::string url) {
    // creating curl object
    CURL *curl;

    // return value
    std::string response;

    // initializing the curl object
    curl = curl_easy_init();

    if (curl) {
        // we must esacpe the url (get rid of bad characters)
        const char *c_url = url.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // send all data to this callback function so we can return it afterwards
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, makeString);

        // data pointer to pass to the write callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the request
        curl_easy_perform(curl);

        // cleanup
        curl_easy_cleanup(curl);
    }

    // error handling
    if (response.size() == 0) {
        return "curl_easy_perform() failed";
    }
    return response;
}

std::string post(std::string url, std::string body) {
    // creating curl object
    CURL *curl;

    // return value
    std::string response;

    // initializing the curl object
    curl = curl_easy_init();

    // initialize the data we want to send (body in this case) as a To_send object
    struct To_send data;
    const char *c_body = body.c_str();
    data.readptr = c_body;
    data.sizeleft = strlen(c_body);

    if (curl) {
        // we must esacpe the url (get rid of bad characters)
        const char *c_url = url.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // send all data to this callback function so we can return it afterwards
        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, makeString);

        // data pointer to pass to the write callback
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // this specifies that we want to post data(body in our case):
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // providing the read_callback function
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

        // now specify which file to upload
        curl_easy_setopt(curl, CURLOPT_READDATA, &data);

        // usefull for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // setting the size of the data we want to send
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)data.sizeleft);

        // perform the request
        curl_easy_perform(curl);

        // cleanup
        curl_easy_cleanup(curl);
    }

    // error handling
    if (response.size() == 0) {
        return "curl_easy_perform() failed";
    }
    return response;
}

std::string put(std::string url, std::string body) {
    // creating curl object
    CURL *curl;

    // initializing the curl object
    curl = curl_easy_init();

    // return value
    std::string response;

    // initialize the data we want to send (body in this case) as a To_send object
    struct To_send data;
    const char *c_body = body.c_str();
    data.readptr = c_body;
    data.sizeleft = strlen(c_body);

    if (curl) {
        // we must esacpe the url (get rid of bad characters)
        const char *c_url = url.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // send all data to this callback function so we can return it afterwards
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, makeString);

        // data pointer to pass to the write callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // enables uploading
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // this specifies that we want to put data(body in our case):
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);

        // providing the read_callback function
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

        // now specify which file to upload
        curl_easy_setopt(curl, CURLOPT_READDATA, &data);

        // usefull for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // setting the size of the data we want to send
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)data.sizeleft);

        // perform the request
        curl_easy_perform(curl);

        // cleanup
        curl_easy_cleanup(curl);
    }

    // error handling
    if (response.size() == 0) {
        return "curl_easy_perform() failed";
    }
    return response;
}

/*
Some examples of how to use the above implemented functions:

int main() {
     curl_global_init(CURL_GLOBAL_DEFAULT);

    Example how to use get() function
    std::cout << get("http://www.example.com") << std::endl;
    


    Example how to use post() function
    std::cout << put("http://httpbin.org/post", "random_text") << std::endl;
    


    Example how to use put() function
    std::cout << put("http://httpbin.org/put", "random_text") << std::endl;

    curl_global_cleanup();
    return 0;
}
*/