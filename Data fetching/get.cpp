using namespace std ;
#include "parse.cpp"
#include "join.cpp"

// arxiv's api seems to prefix this to the tags of all its nodes
std::string prefix = "{http://www.w3.org/2005/Atom}"
std::string base_url = "http://export.arxiv.org/api/query"



/* 
    Yield pairs of the form (author, ID).
    Each pair is produced by searching the authors of each article associated to
    each ID in `id_list`.
*/ 
std::vector<string> authorsFromId (std::vector<string> id_list) {

    typedef vector< tuple<string,string> > tuple_list;
    tuple_list pairs;

    // step 1 : call arxiv's api


    for(std::vector<int>::size_type k = 0; k != id_list.size(); k=k+15) {
        
        std::vector<string> sub(&id_list[k],&id_list[k+15] ; // not really sure about this tho (is it like for buffer where we can call it as such?)

        // for(std::vector<string>::iterator ids = id_list.at(k); ids != id_list.at(k+15); ++ids) (replaced by above)

            // this is a map, where the keys and the values are strings
            std::map<std::string, std::string> params;

            std::string ids ; 
            join(sub, char c, ids) 

            params["id_list"] = ids ; 
            params["max_results"] = std::to_string(id_list.length()) ; 

            // now we want to create the url 
            std::string url = base_url + '?' + "id_list=" + params["id_list"] + ";max_results=" + params["max_results"]


            // step 2 : parse the xml 
            std::string xmldata = urlToString(url) ; 

            std::vector<string> authors = parseAuthors(xmldata) ; 


            // step 3 : iterate over authors & yield names
            for(std::vector<string>::iterator author = authors.start(); author != authors.end(); ++author) {
                pairs.push_back( tuple<string, string>(author, id)  )
            }
        }   

        
    return pairs ; 
    
}

/* 
    Yield pairs of the form (author, ID).
    Each pair is produced by searching the ID of each article associated to
    each author in `authors`.
*/ 
std::vector<string> idsFromAuthor (std::vector<string> authors) {

    // step 1 : call arxiv's api
    for(std::vector<string>::iterator author = authors.start(); author != authors.end(); ++author) {

            // now we want to create the url 
            std::string url = base_url + '?' + "au:" + author


            // step 2 : parse the xml 
            std::string xmldata = urlToString(url) ; 

            std::vector<string> ids = parseIDS(xmldata) ; 

            typedef vector< tuple<string,string> > tuple_list;
            tuple_list pairs;

            // step 3 : iterate over ids 
            for(std::vector<string>::iterator id = ids.start(); id != ids.end(); ++id) {
                res.push_back( tuple<string, string>(author, id)  )
            }
        }   

        return pairs ; 
    
} 
