// compile with : g++ file.cpp -o main `pkg-config --libs libcurl`
// then : ./main http://export.arxiv.org/api/query?search_query=au:Einstein
// need curl and libcurl to be installed 

#include <cstdlib>  // thats the C library <stdlib.h>
#include <cstdio>   // thats the C library <stdio.h>
#include <unistd.h> // thats the unix standard header 
#include <curl/curl.h> 
#include <iostream>
#include <fstream>

#include "references.hpp";

using namespace std;


/* Constructor of References object. Will make the call to libcurl. */ 
References::References(Paper paper) {
    // Converter converter;

    CURL *curl_handle;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    // init the curl session : 
    curl_handle = curl_easy_init();

    // provide the URL to use in the request:
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);     // very useful for libcurl and/or protocol debugging and understanding
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);  // tells the library to shut off the progress meter completely for requests done with this handle. 

    // send all data to this callback function  
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, fillBuffer); // callback function that writes the content of the file into the buffer pointed by *buf

    // data pointer to pass to the write callback:
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buf);

    // perform the request, res will get the return code 
    res = curl_easy_perform(curl_handle);

    // curl_easy_perform(curl_handle);

    // cleanup curl stuff  
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
}

/* Constructor of Converter object. Initializes the variables for the first call to ProcessOutput? Stores the state of the variables. */ 
Converter(){
    // Keep this many previous recent characters for back reference:
    #define oldchar 15

    intextobject  = false ;     
    nextliteral = false ;     
    rbdepth = 0 ;           
    oc[oldchar];      // but whats oc ?? 
}


// buf will be a pointer to ``textBuffer``, into which we want to write the content of the PDF 

/**     
     * This will be the callback function passed to curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, fillBuffer)
     * Called by libcurl (curl_easy_perform(curl_handle)) when data is received. 
     * This function must convert the pdf bytes to text incrementally (as the data arrives). This requires
     * some thought but is doable.
     *
     * The motivation behind this is that It is more efficient than waiting for
     * all the data before converting (look up non-blokcing IO).
     *
     * The text data must be stored in ``textBuffer``.
 */

// can i access oldchar ? if defined in Converter() ? or do i need to do converter.oldchar 

static std::size_t fillBuffer(void *contents, std::size_t size, std::size_t nmemb, std::stringstream *buf) {
    
    // Keep previous chars to get extract numbers etc.:
    for (int j = 0; j < oldchar; j++) oc[j] = ' ';

    size_t len = size*nmemb ; 
    
    for (size_t i = 0; i < len; i++) {
		char c = output[i];     //TO DO : deal with "output"
		if (converter->intextobject) {
			if (converter->rbdepth == 0 && seen2("TD", oc)) {
				// Positioning.
				// See if a new line has to start or just a tab:
				float num = ExtractNumber(oc, oldchar-5);
				if (num > 1.0) {
					buf << 0x0d ;
					buf << 0x0a ; 
				}

				if (num < 1.0) {
					buf << '\t' ;
				}
			}

            if (converter->rbdepth == 0 && seen2("ET", oc)) {
                    // End of a text object, also go to a new line.
                    this->intextobject = false;
                    buf << 0x0d ;
					buf << 0x0a ; 
                } else if (c == '(' && converter->rbdepth == 0 && !nextliteral) {
                    // Start outputting text!
                    this->rbdepth = 1;
                    // See if a space or tab (>1000) is called for by looking
                    // at the number in front of (
                    int num = ExtractNumber(oc, oldchar-1);
                    if (num > 0) {
                        if (num > 1000.0) {
                            buf << '\t' ;
                        } else if (num > 100.0) {
                            buf << ' ' ;
                        }
                    }

                } else if (c==')' && converter->rbdepth==1 && !nextliteral) {
				// Stop outputting text
				this->rbdepth = 0;
			} else if (converter->rbdepth == 1) {
				// Just a normal text character:
				if (c=='\\' && !nextliteral) {
					//Only print out next character no matter what. Do not interpret.
					this->nextliteral = true;
				} else {
					this->nextliteral = false;
					if ( ((c >= ' ') && (c <= '~')) || ((c >= 128) && (c < 255)) ) {
						buf << c ; 
					}
				}
			}
		}

        // Store the recent characters for when we have to go back for a number:
		for (int j = 0; j < oldchar - 1; j++) oc[j] = oc[j + 1];
		oc[oldchar - 1] = c;

		if (!converter->intextobject) {
			if (seen2("BT", oc)) {
				// Start of a text object:
				this->intextobject = true;
			}
		}
	}

}