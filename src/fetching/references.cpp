/** Fetching an arxiv paper's references.
 * 
 * Most of the functionality in the ``PDFConverter`` class comes from an external
 * source. It was simply adapted to our purposes.
 */

#include <cstdlib>  // thats the C library <stdlib.h>
#include <cstdio>   // thats the C library <stdio.h>
#include <unistd.h> // thats the unix standard header 
#include <ctype.h>
#include <string.h>

#include "zlib.h"   // zlib compression library

#include "references.hpp"

#define oldchar 15

using namespace std;


//////////////////////////////////////////////
// for void BulkDownloader::constructPapers()

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <dirent.h>

///////////////////////////////////////////////

// EXTERNAL CODE FROM HERE

// Find a string in a buffer:
static size_t FindStringInBuffer(char* buffer, char* search, size_t buffersize) {
	char* buffer0 = buffer;

	size_t len = strlen(search);
	bool fnd = false;
	while (!fnd) {
		fnd = true;
		for (size_t i=0; i<len; i++) {
			if (buffer[i]!=search[i]) {
				fnd = false;
				break;
			}
		}

		if (fnd)
			return buffer - buffer0;

		buffer = buffer + 1;
		if (buffer - buffer0 + len >= buffersize)
			return -1;
	}

	return -1;
}

// Convert a recent set of characters into a number if there is one.
// Otherwise return -1:
static float ExtractNumber(const char* search, int lastcharoffset) {
	int i = lastcharoffset;
	while (i>0 && search[i]==' ') i--;
	while (i>0 && (isdigit(search[i]) || search[i]=='.')) i--;

	float flt = -1.0;
	char buffer[oldchar+5];
	memset(buffer, 0, sizeof(buffer));
	strncpy(buffer, search+i+1, lastcharoffset-i);

	if (buffer[0] && sscanf(buffer, "%f", &flt)) {
		return flt;
	}

	return -1.0;
}

// Check if a certain 2 character token just came along (e.g. BT):
static bool seen2(const char* search, char* recent) {
if (    recent[oldchar-3]==search[0] 
     && recent[oldchar-2]==search[1] 
	 && (recent[oldchar-1]==' ' || recent[oldchar-1]==0x0d || recent[oldchar-1]==0x0a) 
	 && (recent[oldchar-4]==' ' || recent[oldchar-4]==0x0d || recent[oldchar-4]==0x0a)) {
		return true;
	}

	return false;
}

// This method processes an uncompressed Adobe (text) object and extracts text.
template <typename outstream>
static void ProcessOutput(outstream &ostr, char* output, size_t len) {
	// Are we currently inside a text object?
	bool intextobject = false;

	// Is the next character literal (e.g. \\ to get a \ character or \( to get ( ):
	bool nextliteral = false;

	// () Bracket nesting level. Text appears inside ()
	int rbdepth = 0;

	// Keep previous chars to get extract numbers etc.:
	char oc[oldchar];
	int j = 0;
	for (j = 0; j < oldchar; j++) oc[j] = ' ';

	for (size_t i = 0; i < len; i++) {
		char c = output[i];
		if (intextobject) {
			if (rbdepth == 0 && seen2("TD", oc)) {
				// Positioning.
				// See if a new line has to start or just a tab:
				float num = ExtractNumber(oc, oldchar-5);
				if (num > 1.0) {
					// fputc(0x0d, file);
					// fputc(0x0a, file);
                    ostr << (char)0x0d << (char)0x0a;
				}

				if (num < 1.0) {
					// fputc('\t', file);
                    ostr << '\t';
				}
			}

			if (rbdepth == 0 && seen2("ET", oc)) {
				// End of a text object, also go to a new line.
				intextobject = false;
				// fputc(0x0d, file);
				// fputc(0x0a, file);
                ostr << (char)0x0d << (char)0x0a;
			} else if (c == '(' && rbdepth == 0 && !nextliteral) {
				// Start outputting text!
				rbdepth = 1;
				// See if a space or tab (>1000) is called for by looking
				// at the number in front of (
				int num = ExtractNumber(oc, oldchar-1);
				if (num > 0) {
					if (num > 1000.0) {
						// fputc('\t', file);
                        ostr << '\t';
					} else if (num > 100.0) {
						// fputc(' ', file);
                        ostr << ' ';
					}
				}
			} else if (c == ')' && rbdepth == 1 && !nextliteral) {
				// Stop outputting text
				rbdepth = 0;
			} else if (rbdepth == 1) {
				// Just a normal text character:
				if (c=='\\' && !nextliteral) {
					//Only print out next character no matter what. Do not interpret.
					nextliteral = true;
				} else {
					nextliteral = false;
					if ( ((c >= ' ') && (c <= '~')) || ((c >= 128) && (c < 255)) ) {
						// fputc(c, file);
                        ostr << (char)c;
					}
				}
			}
		}

		// Store the recent characters for when we have to go back for a number:
		for (j = 0; j < oldchar - 1; j++) oc[j] = oc[j + 1];
		oc[oldchar - 1] = c;

		if (!intextobject) {
			if (seen2("BT", oc)) {
				// Start of a text object:
				intextobject = true;
			}
		}
	}
}

template <typename outstream>
void extractText(stringstream &istr, outstream &ostr) {
    // put stream in C-style string
    string temp;
	temp = istr.str();

    int filelen = temp.length();
    char *buffer = new char [filelen + 1];
    int i = 0;
    for(string::iterator c = temp.begin(); c < temp.end(); c++) {
        buffer[i++] = *c;
    }

    buffer[i] = '\0';  // 0 terminated

    // Now search the buffer repeated for streams of data:
    bool morestreams = true;
    while (morestreams) {
        //Search for stream, endstream. We ought to first check the filter
        //of the object to make sure it if FlateDecode, but skip that for now!
        size_t streamstart = FindStringInBuffer (buffer, (char*)"stream", filelen);
        size_t streamend   = FindStringInBuffer (buffer, (char*)"endstream", filelen);

        if (streamstart>0 && streamend>streamstart) {
            //Skip to beginning and end of the data stream:
            streamstart += 6;

            if (buffer[streamstart]==0x0d && buffer[streamstart+1]==0x0a) streamstart+=2;
            else if (buffer[streamstart]==0x0a) streamstart++;

            if (buffer[streamend-2]==0x0d && buffer[streamend-1]==0x0a) streamend-=2;
            else if (buffer[streamend-1]==0x0a) streamend--;

            //Assume output will fit into 10 times input buffer:
            size_t outsize = (streamend - streamstart)*10;
            char* output = new char [outsize]; memset(output, 0, outsize);

            //Now use zlib to inflate:
            z_stream zstrm; memset(&zstrm, 0, sizeof(zstrm));

            zstrm.avail_in = streamend - streamstart + 1;
            zstrm.avail_out = outsize;
            zstrm.next_in = (Bytef*)(buffer + streamstart);
            zstrm.next_out = (Bytef*)output;

            int rsti = inflateInit(&zstrm);
            if (rsti == Z_OK) {
                int rst2 = inflate (&zstrm, Z_FINISH);
                if (rst2 >= 0) {
                    //Ok, got something, extract the text:
                    size_t totout = zstrm.total_out;
                    ProcessOutput<outstream>(ostr, output, totout);
                }
            }

            delete[] output; output=0;
            buffer+= streamend + 7;
            filelen = filelen - (streamend+7);
        } else {
            morestreams = false;
        }
    }
}

// EXTERNAL CODE ENDS NOW

////////////////////////
//  References Class  //
////////////////////////

References::References(Paper paper, std::string text) : textBuffer(text) {
}


////////////////////////
// PDFConverter Class //
////////////////////////

/**
 * Launches the curl_easy_setopt (URL, writefunction etc)
 * Input : the id of the pdf we want to convert. We have to check whether we've already converted it with the Bulk method.
 * 				so has to have access to the attributes of the BulkDownloader class ? 
 */
PDFConverter::PDFConverter(std::string id) {
	// curl_global_init(CURL_GLOBAL_ALL);  i'm not sure if we should do it here, we only need to do it once per program
	CURL *handle = curl_easy_init();

	// creating the url
	std::string URL = "https://arxiv.org/pdf/" + id;

	curl_easy_setopt(handle, CURLOPT_URL, URL);
	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);	// very useful for libcurl and/or protocol debugging and understanding
	curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L); // tells the library to shut off the progress meter completely for requests done with this handle. 

	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, PDFConverter::fillBuffer); // set callback for writing received data (pass a pointer to your callback function)
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &(this->pdfBuffer)); // will write the data to the pdfBuffer given with this option
	// not sure how to access pdfBuffer though

	// only things missing for libcurl, that will be taken care of by the Papers object : 
	// curl_easy_perform(curl_handle);
	// curl_easy_cleanup(curl_handle);
	// curl_global_cleanup(); 
}

// replaced by function below. mark deleted ?
PDFConverter::PDFConverter(std::stringstream *pdf) {
	pdfBuffer << pdf->str();
}

// used when constructing converter with an already obtained PDF
// i.e. with the output of the bulk downloads
PDFConverter::PDFConverter(PDF pdf) {
	// maybe an easy way to do this is : 
	std::ifstream input( pdf, std::ios::binary );
    std::vector<unsigned char> pdfBuffer(std::istreambuf_iterator<char>(input), {}); 	// copies all data into buffer

	/* that doesnt look efficient to me 
	fstream file ; 
	f = file.open ( pdf, ios::in ) ; 
	if(!file){
		cout << "Error encountered while opening file" << endl ; 
	}
	char ch ; 
	while(!file.eof()){
		file >> ch;
		pdfBuffer << ch ; 
	}
	file.close();
	*/ 
}

/**
 * Callback function passed to CURLOPT_WRITEFUNCTION
 * Writes the content of the pdf into std::stringstream pdfBuffer;
 */
size_t PDFConverter::fillBuffer(char *contents, size_t size, size_t nmemb, stringstream *buf) {
    *buf << contents;
}

string PDFConverter::getText() {
    extractText<stringstream>(pdfBuffer, textBuffer);
	std::string temp = textBuffer.str();
	return temp;
}


////////////////////////
//    Papers Class    //
////////////////////////

void Papers::initialize() {
	this->mhandle = curl_multi_init() ; 
}

void Papers::perform() {
	curl_multi_perform(this->mhandle, stillRunning);
}

void Papers::cleanup() {
	curl_multi_cleanup(this->mhandle) ; 
}

// not a priority anymore
Papers::Papers(std::vector<std::string> ids) : ids(ids) {
	initialize();

	// For each id in ids, create a PDFConverter object 
	for(std::vector<std::string>::iterator id = ids.begin() ; id != ids.end() ; id++){
		PDFConverter pdfc = PDFConverter(*id);
		curl_multi_add_handle(mhandle, pdfc.handle);
	}

	perform(); // or Papers::perform ? 
	//  will write the number of handles that still transfer data in stillRunning 

	// kinda lost with the select thingy to know when a tranfer is done and when we can get the data (i.e. call getText right?)

	cleanup(); // or  Papers::cleanup()?
}

// this is the priority
Papers::Papers(std::vector<std::string> ids, std::vector<PDF> pdfs) : ids(ids) {
    if(ids.size() != pdfs.size())
        throw "argument error";

    for(int i = 0; i < ids.size(); i++) {
    	PDFConverter pdfc(pdfs[i]);
        Paper paper(ids[i]);
        References refs(paper, pdfc.getText());

        // put found references in this object
        references.insert(references.end(), refs.begin(), refs.end());
    }
}

std::vector<std::pair<Paper, Paper>> Papers::getReferences() {
    return this->references;  // explicitness
}


////////////////////////////////
//    BulkDownloader Class    //
////////////////////////////////


void BulkDownloader::downloadTar() {
    std::string cmd = "aws s3 cp --request-payer requester s3://arxiv/pdf/" + which + " " + folder;
	system(cmd.c_str());
}

void BulkDownloader::decompress() {
    std::string cmd = "tar -xvf " + folder + " " + which;
	system(cmd.c_str());
}

/** 
 * opening any folder and saving all file-names in a vector<string>
 * used in BulkDownloader::constructPapers()
 */
vector<string> openDir(string path) {
	DIR    *dir;
    dirent *pdir;
    vector<string> files;
    dir = opendir(path.c_str());
    while(pdir = readdir(dir))
        files.push_back(pdir->d_name);

    return files;
}

Papers BulkDownloader::constructPapers() {
	vector<string> f ;
    fstream file;
    map<string, int> m_query;
    string c;

	f = openDir(this->folder);  // might need to give the path ?

    std::vector<std::string> ids;
    std::vector<PDF> pdfs;
	for (vector<string>::iterator s = f.begin(); s != f.end(); s++) {
        // push id
        ids.push_back(s->substr(0, s->size()-4));

        // push whole pdf text - do we need the binary marker ?
        std::ifstream pdf_stream(*s, std::ios::binary);
        std::stringstream buffer;
        buffer << pdf_stream.rdbuf();
        pdfs.push_back(PDF(buffer.str()));
    }

    Papers papers(ids, pdfs);
    return papers;
}


// map from papers to all that they reference
// big object. not scalable for real data (> 1.5 million docs)
// no time to do better
std::map<std::string, std::vector<std::string>> allReferences;




/** 
 * @brief to write the content of allReferences to a file
 * @param data to be written in the file
 * @param filename name of the file to be created and 
 * written into
 * (verified, i.e. works)
 */
void writeFile(std::map<std::string, std::vector<std::string>> data , std::string filename){
	std::string file = filename + ".txt" ; // also a prefix to say where its going? 
	std::ofstream fs(file);

	if(!fs){
		std::cerr<<"Cannot open the output file."<<std::endl;
	}

	// we write on the file in the following format :
	// paper
	// paper_referenced1|paper_referenced_2|......|paper_referenced_n|
	// paper
	// etc. 

	for(std::map<std::string, std::vector<std::string>>::iterator pair = data.begin(); pair != data.end() ; pair++){
		fs << pair->first << endl ; 
		
		for(std::vector<std::string>::iterator ref = pair->second.begin() ; ref != pair->second.end() ; ref++){
			fs << *ref << "|" ; 
		}

		fs << endl ; 

	}


	fs.close() ; 

}

/** 
 * @brief get allReferences back from a file
 * @param filename file to be read from
 */
std::map<std::string, std::vector<std::string>> readFile(std::string filename){
	std::map<std::string, std::vector<std::string>> res ; 
	std::ifstream file(filename, std::ifstream::in);
	if(file.is_open()){
		std::string line ;
		int index = 0 ; // will allow us to know where we stand in the file
		std::string key ; 

		while(getline(file,line)){

			if(!index){ // index = 0 : we stand in a 'paper' line 
				key = line ; // so we just store the value as 'key'
			}

			else {
				// index = 1 : we stand in a 'paper_referenced1|paper_referenced_2|..
				// ..|paper_referenced_n|' line
				// so we parse the line to get the each reference 

				std::vector<std::string> references ; 
				std::string delimiter =  "|" ;
				size_t pos = 0 ; 
				std::string token ;

				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
					references.push_back(token); 
					line.erase(0, pos + delimiter.length());
				}

				res[key] = references ; 
			}

			index = 1 - index ;

		}
	} 
	return res ; 
}




// must be called a number of times.
void setUpReferences(std::string folder, std::vector<std::string> archives) {
    for(auto archive : archives) {
        BulkDownloader bd(archive, folder);
        bd.downloadTar();
        bd.decompress();
        Papers papers = bd.constructPapers();

        for(auto ref : papers.getReferences())
            allReferences[ref.first.id].push_back(ref.second.id);
    }
}

// must find some kind of way to serialize / deserialize `allReferences`
std::vector<std::pair<Paper, Paper>> getReferences(std::vector<Paper> papers) {
    std::vector<std::pair<Paper, Paper>> refs;

    for(auto from : papers) {
        for(auto to : allReferences[from.id])
            refs.push_back(std::make_pair(from, Paper(to)));
    }

    return refs;
}
