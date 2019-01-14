#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>

#include "declaration_knn.hpp"
/* constructor for name
get the interactions in the data base
get the cluster (list of name of researchers) of jules
get person identity vector or a paper identity vectior*/
/*verifier que edge.paper est une string d'un nom de papier */

/** @brief Get a recommendation (Title of a paper) for a client
 * 
 * @details Using the cluster to which belong the client, we choose k neigbours in this cluster
 * The papers read by those neigbours are potential recommendations. We return one of those papers with a probability that depends on the predicted rating of this paper by our client
 * @param integer k: the number of neigbours in the cluster of the client that we will take into account
 * 
 * @return the title of a paper that we recommend to the client according to his preferences
 */
std::string Person::getRecommendation(int& k) {
    std::vector<std::string> a_list_of_interaction_papers;
    a_list_of_interaction_papers = get_k_NeighborsInteractions(int& k);
    std::pair<std::vector<int>,std::vector<std::string>> result;
    result = getRatings_of_papers(std::vector<std::string>& a_list_of_interaction_papers);
    std::string recommendation;
    recommendation = get_a_Title_paper(std::pair<std::vector<int>,std::vector<std::string>>& result);
    return recommendation;
}

/** @brief get the name of the papers read by k neighbours of the client 
 * 
 * @details 
 * 
 * @param integer k : number of neighbours in the cluster of the client that we will take into account
 * 
 * @return a vector of name of papers that has been read by those k neighbours
 */

std::vector<std::string> Person::get_k_NeighborsInteractions(int& k) const {
    std::vector<array*> list_of_neighbours_in_cluster;
    std::vector<array*> list_of_neighbours_in_cluster = author.cluster(); /*get the list of people in the cluster of my user ID =  resultat de lalgo de jules, stocker dans la base de donnée*/
    array** total_interactions = new array*[list_of_neighbours_in_cluster.size()];
    int i = 0;
    for (nei = list_of_neighbours_in_cluster.begin(); nei != list_of_neighbours_in_cluster.end(); nei++)
    {
        Driver driver("folder");
        std::vector<Edge> interactions_pairs_nei = driver.getFrom(nei);
        std::vector<std::string> interactions_nei;
        for(int i =0; i<interactions_pairs.size();i++) {
            interactions.push_back(interactions_pairs_nei[i].paper.id)
            }
        std::vector<std::string> interactions_nei;
        for(int i =0; i<interactions_pairs.size();i++) {
        interactions.push_back(interactions_pairs[i].paper.id)
    }
    
        total_interactions[i] = interactions_nei;
        
    }
    std::vector<array*> knn_info;
    for(l = 0;l<=k,l++) {
        n = rand() % list_of_neighbours_in_cluster.size() + 1;
        knn_info[l] = total_interactions[n]; /* knn info est un liste de liste de papiers, certains papiers peuvent apparaitrent plusieurs fois*/

    }
    
    std::vector<std::string> a_list_of_interaction_papers;
    
    for(int i = 0;i<=knn_info.size();i++) {
        for(int k = 0;k<=knn_info[i].size(),k++) {
            a_list_of_interaction_papers.push_back(knn_info[i][k])
        }
    }
    return a_list_of_interaction_papers;
}

/** @brief get the predicted ratings of a list of papers for the client
 * 
 * @details given a list of papers, we use the preferences (thourgh the vector of the client) to predict the ratings of each paper of the list
 * 
 * @param vector of strings : the vector contains titles of papers 
 * @return a pair composed of a vector of float (predicted ratings) and a vector of name of papers (the rating at index i corresponds to the paper at the index i in the vector of papers) 
 */
 
std::pair<std::vector<float>,std::vector<std::string>>  Person::getRatings_of_papers(std::vector<std::string>& list_of_papers) { /*list of papers sera id.get_k_Interactions*/
    std::vector<float> ratings_of_ID;
    Driver driver("folder");
    std::vector<Edge> interactions_pairs = driver.getFrom(author);
    std::vector<std::string> id_interactions;
    for(int i =0; i<interactions_pairs.size();i++) {
        interactions.push_back(interactions_pairs[i].paper.id)
    }
    std::vector<std::string> name_of_papers_of_ID;
    for (int i=0;i<list_of_papers.size();i++){
        for(k=0;k!= ratings_of_ID.size();k++){
            std::string name_paper = list_of_papers[i];
            if(name_paper in id_interactions or in name_of_papers_of_ID {
                break;
    }
            else {
                VectorAccessor<int 30> vector_id_researcher = get_vector(author);
                VectorAccessor<int 30> vector_id_paper = get_vector(name_paper);
                float rating_id = vector_id_researcher.dot(vector_id_paper); 
                ratings_of_ID.push_back(rating_ID);
                name_of_papers_of_ID.push_back(name_paper);

            }
            }
    
    

    }
    std::pair<std::vector<float>,std::vector<std::string>> result;
    result.first = ratings_of_ID;
    result.second = name_of_papers_of_ID;
    return result;
    }
/** @brief get the predicted ratings of a list of papers for the client
 * 
 * @details given a list of papers, we use the preferences (thourgh the vector of the client) to predict the ratings of each paper of the list
 * 
 * @param integer k : number of neighbours in the cluster of the client that we will take into account
 * 
 * @return a pair composed of a vector of float (predicted ratings) and a vector of name of papers (the rating at index i corresponds to the paper at the index i in the vector of papers) 
 */
std::string Person::get_a_title_paper(std::pair<std::vector<int>,std::vector<std::string>>& result) {
        int proba;
        int sum = sum(result.first);
        int random = rand();
        int interval = 0;
        for(i = 0;i<=result.first.size(),i++){
            if(interval>random*sum){
                break
            }
            interval+= result.first[i];
        }
        proba = result.first[i-1];
    return result.second[i-1];
}