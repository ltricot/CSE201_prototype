// compile with : g++ file.cpp -o main `pkg-config --libs libcurl`
// then : ./main http://export.arxiv.org/api/query?search_query=au:Einstein
// ./main http://export.arxiv.org/api/query?search_query=hep-ph/9807350
// need curl and libcurl to be installed 

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
// we're not actually using this 
const char* stringToCharpt(std::string str) {
    const char* c = str.c_str() ; 
    return c ;
}

// converting a string to a char vector
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


// receives an url for an arXiv's API request and turns the XML result into a string that we can parse
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


// from an article's id, get name of all authors
vector<string> parseAuthors(std::string xmlString){

    // convert xmlString to vector<char>
    vector<char> url = stringToCharVct(xmlString) ; 

    // we need it to be a null-terminated string : 
    url.push_back('\0'); 

    xml_document<> doc; 

    // parse the buffer 
	doc.parse<0>(&url[0]);


    // Find our root node
	xml_node<> *pRoot = doc.first_node("feed");
	xml_node<> *pEntry =pRoot->first_node("entry");

    typedef vector<string> tuple_list;
    tuple_list authors;

    //get the authors' name
	for(xml_node<> *pAuthor=pEntry->first_node("author"); pAuthor; pAuthor=pAuthor->next_sibling("author"))
	{
		xml_node<> *pName=pAuthor->first_node("name"); 
        authors.push_back(pName->value()) ;
	}

    return authors ;

}

// from author, get ids of all publications
vector<string> parseIDS(std::string xmlString){

    // convert xmlString to vector<char>
    vector<char> url = stringToCharVct(xmlString) ; 

    // we need it to be a null-terminated string : 
    url.push_back('\0'); 

    xml_document<> doc; 

    // parse the buffer 
	doc.parse<0>(&url[0]);


    // Find our root node
	xml_node<> *pRoot = doc.first_node("feed");
	xml_node<> *pEntry =pRoot->first_node("entry");

    typedef vector<string> tuple_list;
    tuple_list ids;

    // get the ids
    for(xml_node<> *pEntry=pRoot->first_node("entry"); pEntry; pEntry=pEntry->next_sibling("entry"))
	{
		xml_node<> *pID =pEntry->first_node("id"); //get the id
		ids.push_back(pID->value()) ;
	}

    return ids ;
}

/* 
int main(int argc, char *argv[]){
    std::string s ;
    s = urlToString(argv[1]) ;
    std::cout << s << std::endl ;

    // parseString(s) ;

    vector<string> authors ; 
    authors = parseAuthors(s) ;
    for (std::vector<string>::const_iterator i = authors.begin(); i != authors.end(); ++i){
        std::cout << *i << std::endl;
    }
    
    vector<string> ids ; 
    ids = parseIDS(s) ; 
    for (std::vector<string>::const_iterator i = ids.begin(); i != ids.end(); ++i){
        std::cout << *i << std::endl;
    }
    return 0 ; 
}
*/ 