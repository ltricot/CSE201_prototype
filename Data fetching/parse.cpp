// compile with : g++ file.cpp -o main `pkg-config --libs libcurl`

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include <cstdlib>  // thats the C library <stdlib.h>
#include <cstdio>   // thats the C library <stdio.h>
#include <unistd.h> // thats the unix standard header 
#include <curl/curl.h> 

using namespace rapidxml;
using namespace std;

// converting a string to a char pointer 
const char* stringToCharpt(std::string str) {
    const char* c = str.c_str() ; 
    return c ;
}

// converting a string to a char vector
// maybe instead of doing this i could directly put this in urlToString which would make it urlToCharVector ?
// i dont know which one is the most efficient 

std::vector<char> stringToCharVct(std::string s) {
    std::vector<char> v(   s.begin(), s.end()   ); 
    return v ; 

} 


static size_t makeString(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

std::string urlToString(const char* url) {
    CURL *curl_handle;
    CURLcode res;

    std::string s ; 

    // const char* url = string_to_charpt(s) ; 

    curl_global_init(CURL_GLOBAL_ALL);
    // init the curl session : 
    curl_handle = curl_easy_init();
    // provide the URL to use in the request :
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);        
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);     // very useful for libcurl and/or protocol debugging and understanding
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);  // tells the library to shut off the progress meter completely for requests done with this handle. 

    // send all data to this callback function  
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, makeString);
    // data pointer to pass to the write callback:
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &s );

    // perform the request, res will get the return code 
    res = curl_easy_perform(curl_handle);

    // curl_easy_perform(curl_handle);

    // cleanup curl stuff  
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return s ;
}



void parseString(std::string xmlString){
    // convert xmlString to vector<char>
    vector<char> url = stringToCharVct(xmlString) ; 
    // we need it to be a null-terminated string : 
    url.push_back('\0'); 

    xml_document<> doc; 

    /* 
    const char* xmldata = stringToCharpt(xmlString) ;

    // Convert xml to vector<char>
    vector<char> buffer(xmldata, xmldata + xmldata.length());
    // we need it to be a null-terminated string : 
	buffer.push_back('\0');
    */ 
    // parse the buffer 
	doc.parse<0>(&url[0]);

    // Find our root node
	xml_node<> *pRoot = doc.first_node("feed");
	xml_node<> *pEntry =pRoot->first_node("entry");
	xml_node<> *pID =pEntry->first_node("id"); //get the id
	std::cout << pID->value()<<std::endl;
    xml_node<> *pUpdate =pEntry->first_node("updated"); //get the date
    std::cout << pUpdate->value()<<std::endl;
	for(xml_node<> *pAuthor=pEntry->first_node("author"); pAuthor; pAuthor=pAuthor->next_sibling("author"))
	{
		xml_node<> *pName=pAuthor->first_node("name"); //get the author names
		std::cout<< pName->value() <<std::endl; 
	}

}



int main(int argc, char *argv[]){
    std::string s ;
    s = urlToString(argv[1]) ;
    std::cout << s << std::endl ; 
    parseString(s) ; 
    return 0 ; 
}