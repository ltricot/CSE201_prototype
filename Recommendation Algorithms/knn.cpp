#include <iostream>
#include <string>
#include <stdlib.h>
#include <array>

std::string Knn_(std::string& id, int& k){
    array<array*, 10> list_of_neighbours_in_cluster;/* taille
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
    array<std::string, howmany differentpapers> name_of_papers_of_ID; /* je ne sais pas comment allocate l'espace pour cet aray, car je ne sais pas la taille qu'il aura, j'aimerai pouvoir rajouter au fur et a mesure de l'espace */
    array<float, howmany differentpapers> ratings_of_ID; /* chose sure est que name_of_papers_of_ID and ratings ID auront la meme taille: l'un correspond aux noms de papiers que je pourrai potentiellement conseiller à mon ID, et l'autre correspond aux predictions de ratings de mon ID sur ces recommendations potentielles*/
    interactionsofID = id.interactions; /* j'assume que chaque user a un data attribute called interactions qui est une listes de nom de papiers avec lequels il a interagi*/
    
    for (paper = knn_info.begin(); paper != knn_info.end();paper++){ /* paper est un interateur qui itère sur un array de array, chaque pointer pointe donc vers un array qui est une liste de nom de papier*/
        for(k=0;k!= paper.size;k++){
            std::string name_paper = *paper[k]; /*ici, papier est un des pointeurs de knn info et pointe vers une liste de papiers, ainsi papier[k]est le nom du k-ième papier de cette liste */
            if(name_paper in name_of_papers_of_ID or if name_paper in interactionsofID{ /* si le nom du papier a deja été pris en compte (si c'est dans name of papers of ID) ou si ID a déja interagit avec ce papier dans le passé alors je le prends pas en compte*/
                break;
    }
            else {
                float rating_id = vector_identity_of_ID*vector_identity_of_"name_paper" /* je calcule le rating de prediction de user ID concernant chaque film recommentation  potentielle, pb: je ne sais pas vraiment comment les vecteurs identité du user et des papiers seront*/
                ratings_of_ID.append(rating_id); /* l'élement i de ratings of ID sera le rating du paper dont le nom est stoclé dans name_of_papers_of ID à l'indice i*/
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
    return name_of_papers_of_ID[i-1]/*the name of the film that corresponds to this ratings_of_ID


    }                        
}
}