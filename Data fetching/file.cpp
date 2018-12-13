// compile with : g++ file.cpp -o main `pkg-config --libs libcurl`
// then : ./main http://export.arxiv.org/api/query?search_query=au:Einstein
// need curl and libcurl to be installed 

#include <cstdlib>  // thats the C library <stdlib.h>
#include <cstdio>   // thats the C library <stdio.h>
#include <unistd.h> // thats the unix standard header 
#include <curl/curl.h> 
#include <iostream>
#include <fstream>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
int main(int argc, char *argv[])
{
  CURL *curl_handle;
  static const char *pagefilename = "page.out";
  FILE *pagefile;
 
  if(argc < 2) {
    printf("Usage: %s <URL>\n", argv[0]);
    return 1;
    }
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
                             // CURLOPT_URL - provide the URL to use in the request
 
  /* Switch on full protocol/debug output while testing */ 
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
                            // very useful for libcurl and/or protocol debugging and understanding
 
  /* disable progress meter, set to 0L to enable and disable debug output */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
                            // tells the library to shut off the progress meter completely for requests done with this handle. 

/* When curl is invoked to transfer data (either uploading or downloading) it can show that meter in the terminal 
screen to show how the transfer is progressing, namely the current transfer speed, how long it has been going on 
and how long it thinks it might be left until completion. */
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
                            // set callback for writing received data (pass a pointer to your callback function)
 
  /* create the file */
  std::ofstream outfile ("test.xml");
  /* open the file */ 
  pagefile = fopen("test.xml", "wb");
  if(pagefile!= NULL) {
 
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
                        // will write the data to the FILE * given with this option
 
    /* get it */ 
    curl_easy_perform(curl_handle);
 
    /* close the header file */ 
    fclose(pagefile);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
 
  return 0;
}