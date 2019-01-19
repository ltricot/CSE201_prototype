#include "driver.hpp"
#include "declaration_knn.hpp"

// to compile : order of the arguments : 
// cdta vdata clusters keyfile author k 

int main(int argc, char *argv[]) {
    std::string cdata = argv[1]; //name of databased filled by quickrefs

    std::string vdata = argv[2]; //name of database filled by matrix factorization 
                    // from which we want to read

    std::string clusters = argv[3]; //name of database containing clusters

    std::string keyfile = argv[4]; //labels for clustering 

    std::string authorName = argv[5]; //name of an author

    int k = atoi(argv[6]); //the number of neigbours in the cluster of the client that we will take into account

    Author author(authorName);

    Person person(author, cdata, vdata, clusters, keyfile);

    std::string title ; //the title of a paper that we recommend to the client according to his preferences
    title = person.getRecommendation(k);

    std::cout << title << std::endl ; 
}