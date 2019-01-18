#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>
#include <vector>
#include <algorithm>
#include "../../../module_eigen/Eigen/Eigen"
#include "declaration_knn.hpp"
/* constructor for name
get the interactions in the data base
get the cluster (list of name of researchers) of jules
get person identity vector or a paper identity vectior*/
/*verifier que edge.paper est une string d'un nom de papier */

/** @brief Get a recommendation (Title of a paper) for a client
 * 
 * @details Using the cluster to which belong the client, we choose k neighbours in this cluster
 * The papers read by those neigbours are potential recommendations. We return one of those papers with a probability that depends on the predicted rating of this paper by our client
 * @param integer k: the number of neigbours in the cluster of the client that we will take into account
 * 
 * @return the title of a paper that we recommend to the client according to his preferences
 */
std::string Person::getRecommendation(int &k) {
    std::vector<std::string> a_list_of_interaction_papers;
    a_list_of_interaction_papers = this->get_k_NeighborsInteractions(k);
    std::pair<std::vector<float>,std::vector<std::string>> result;
    result = this->getRatings_of_papers(a_list_of_interaction_papers);
    std::string recommendation;
    recommendation = this->get_a_title_paper(result);
    return recommendation;
}

/** @brief get the titles of the papers read by k neighbours of the client 
 * 
 * @details 
 * 
 * @param integer k : number of neighbours in the cluster of the client that we will consider
 * 
 * @return a vector of name of papers that has been read by those k neighbours
 */

std::vector<std::string> Person::get_k_NeighborsInteractions(int &k) {
    std::vector<Author> list_of_neighbours_in_cluster;
    list_of_neighbours_in_cluster = this->cluster; /*get the list of people in the cluster of my user:algo of jules and marine: .cluster gives a list of AUthor types*/
    std::vector<std::vector<std::string>> total_interactions;
    int i = 0;
    for (std::vector<Author>::iterator nei = list_of_neighbours_in_cluster.begin(); nei != list_of_neighbours_in_cluster.end(); nei++)
    {   
        Driver driver("folder");
        std::vector<Edge> interactions_pairs_nei = driver.getFrom(*nei);
        std::vector<std::string> interactions_nei;
        for(int i =0; i<=interactions_pairs_nei.size();i++) {
            interactions_nei.push_back(interactions_pairs_nei[i].paper.id); /*because Edge is composed of a paper and a author and paper has an atribute .id which is a string*/
            }
        total_interactions[i] = interactions_nei;
        i++;
    }

    std::vector<std::vector<std::string>> knn_info;
    for(int l = 0;l<k;l++) {
        
        int n = rand() % list_of_neighbours_in_cluster.size() + 1;
        knn_info[l] = total_interactions[n]; /* knn info is a vector of elements from total interactions (its element are =vector of string), the string is the name of a paper some papers can appears in several times : it is a Paper.id*/

    }
    
    std::vector<std::string> a_list_of_interaction_papers;
    
    for(int i = 0;i<knn_info.size();i++) {
        for(int k = 0;k<knn_info[i].size();k++) {
            a_list_of_interaction_papers.push_back(knn_info[i][k]);
        }
    }
    return a_list_of_interaction_papers; /*this is a list of name of papers: the type is string because it is a Paper.id*/
}

/** @brief get the predicted ratings of a list of papers for the client
 * 
 * @details given a list of papers, we use the preferences (through the vector of the client) to predict the ratings of each paper of the list
 * 
 * @param vector of strings : the vector contains titles of papers 
 * @return a pair composed of a vector of float (predicted ratings) and a vector of name of papers (the rating at index i corresponds to the paper at the index i in the vector of papers) 
 */

std::pair<std::vector<float>,std::vector<std::string>>  Person::getRatings_of_papers(std::vector<std::string> &list_of_papers) { /*list of papers sera id.get_k_Interactions*/
    std::vector<float> ratings_of_ID;
    Driver driver("folder");
    std::vector<Edge> interactions_pairs = driver.getFrom(this->author);
    std::vector<std::string> id_interactions; /*name of the papers (string) with which the person has interacted with*/
    for(int i =0; i<interactions_pairs.size();i++) {
        id_interactions.push_back(interactions_pairs[i].paper.id);
    }
    std::vector<std::string> name_of_papers_of_ID;
    for (int i=0;i<list_of_papers.size();i++){
        std::string name_paper = list_of_papers[i]; /*name paper is a Paper.id thus it is a string */
        if((std::find(id_interactions.begin(),id_interactions.end(),name_paper)!= id_interactions.end()) || (std::find(name_of_papers_of_ID.begin(),name_of_papers_of_ID.end(),name_paper)!= name_of_papers_of_ID.end())){
            break;
            }
        else {
            VectorAccessor<30> v("folder2");
            Eigen::Matrix<double ,30,1> vector_id_researcher = v.get_vector(this->author);
            Eigen::Matrix<double ,30,1> vector_id_paper = v.get_vector(Paper(name_paper));
            float rating_id = vector_id_researcher.dot(vector_id_paper);                 
            ratings_of_ID.push_back(rating_id);
            name_of_papers_of_ID.push_back(name_paper);

        }
    }
    
    

    
    std::pair<std::vector<float>,std::vector<std::string>> result;
    result.first = ratings_of_ID;
    result.second = name_of_papers_of_ID; /* result.second is a list of Paper.id, hence a list of string*/
    return result;
    }
/** @brief choose a paper among a list of paper wth higher probability the more the predicted rating of this paper by the client is important
 * 
 * @details 
 * 
 * @param a pair composed of a vector of float (predicted ratings) and a vector of name of papers (the rating at index i corresponds to the paper at the 
 *
 * @return a name of a paper from the vector of paper names given as parameter
 */
std::string Person::get_a_title_paper(std::pair<std::vector<float>,std::vector<std::string>> &result) {
        int proba;
        float sum;
        for(std::vector<float>::iterator it = result.first.begin(); it != result.first.end(); ++it){
                sum+= *it;
        }
        
        int random = rand();
        int interval = 0;
        int k = 0;
        for(int i = 0;i<=result.first.size();i++){
            k = i;
            if(interval>random*sum){
                break;
            }
            interval+= result.first[i];
        }
        proba = result.first[k-1];
    return result.second[k-1];
}
