#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>

std::string Knn_(std::string& id, int& k){
    array<array*, 10> list_of_neighbours_in_cluster;/* taimme
    array list_of_neighbours_in_cluster = id.cluster(); /*get the list of people in the cluster of my user ID =  resultat de lalgo de jules, stocker dans la base de donnée*/
    array** total_interactions = new array*[list_of_neighbours_in_cluster.size];
    int i = 0;
    for (nei = list_of_neighbours_in_cluster.begin(); nei != list_of_neighbours_in_cluster.end(); nei++)
    {
        // Access the object through iterator
        array interactions = nei->interactions; /*il faudrait que chaque user ait une data attributes interactions qui est une liste de papier avec lequels il a interagi*/
        total_interactions[i] = &interactions;
        
    }
    array<array*,k> knn_info;
    for(l = 0;l<=k,l++) {
        n = rand() % list_of_neighbours_in_cluster.size + 1;
        knn_info[l] = total_interactions[n]; /* knn info est un liste de liste de papiers, certains papiers peuvent apparaitrent plusieurs fois*/

    }
    array<std::string, howmany differentpapers> name_of_papers_of_ID;
    array<float, howmany differentpapers> ratings_of_ID;
    interactionsofID = id.interactions;
    
    for (paper = knn_info.begin(); paper != knn_info.end();paper++){
        for(k=0;k!= paper.size;k++){
            std::string name_paper = *paper[k];
            if(name_paper in name_of_papers_of_ID or if name_paper in interactionsofID{
                break;
    }
            else {
                float rating_id = vector_identity_of_ID*vector_identity_of_"name_paper"
                ratings_of_ID.append(rating_id);
                name_of_papers_of_ID.append("name_paper");

            }
            }
    
    int proba;
    int sum = sum(ratings_of_ID);
    int random = rand();
    int interval = 0;
    for(i = 0;i<=ratings_of_ID.size,i++){
        if(interval>random*sum){
            break
        }
        interval+= ratings_of_ID[i]
    }
    proba = ratings_of_ID[i-1];
    return /*the name of the film that corresponds to this ratings_of_ID


    }                        
}
}