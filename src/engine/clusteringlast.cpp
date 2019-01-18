// based on the label propagation principle
#include "clusteringlast.hpp"
using std::exp;



int Cluster::T =2;

//@brief function that initialize the vector<int> label
void Cluster::initializelabel(){
    for (int i=0;i<sizeInput;i++){
        label.push_back(i);
    }
}

/**@brief function that thanks to the similarities argument can construct the nodes vector and the neighbors vector std::vector<std::map<int,double>>
*@details add each author in the nodes vector thanks to this each author is characterized by an int (the index)
*construct the neighbors vector: for each author (so each index in nodes) construct a map that associates to each of its neighbor the similarity
*/
void Cluster::findneighbors(std::vector<Friends> & similarities){
    int c=0;
    for (std::vector<Friends>::iterator it=similarities.begin();it!=similarities.end();it++){
        Author au1 = std::get<0>(*it);
        Author au2 = std::get<1>(*it);
        double sim = std::get<2>(*it);
        int pos1;
        int pos2;
        if (std::map<Author,int>::iterator it1==nodes.find(au1)){
            nodes.insert(std::make_pair(au1,c));
            nodesindex.insert(std::make_pair(c,au1));
            neighbors.push_back(std::vector<std::pair<int,double>>());
            pos1=c;
            c++;
        }
        else{
            pos1=nodes[au1];
        }
        if (std::map<Author,int>::iterator it2=nodes.find(au2)){
            nodes.insert(std::make_pair(au2,c));
            nodesindex.insert(std::make_pair(c,au2));
            neighbors.push_back(std::vector<std::pair<int,double>>());
            pos2=c;
            c++;
        }
        else{
            pos2=nodes[au2];
        }
        neighbors[pos2].push_back(std::make_pair(pos1,sim));
        neighbors[pos1].push_back(std::make_pair(pos2,sim));
    }
}
/**@brief create the allCDF vector
  * @details for each author create a cdf by doing a vector that at index j associates the probability to choose one of the previous
  * neighbors encountered
*/

void Cluster::getCDF(){
    for (int i=0;i<sizeInput;i++){
        Eigen::ArrayXd allSim; // vector of similarities between the ith node and all its neighbors
        Eigen::ArrayXd allProb; //vector of e^si/sum(e^si)
        allSim.resize(neighbors[i].size());
        allProb.resize(neighbors[i].size());
        int c=0;
        //iterate over the vector neighbors[i] to have an array of similarities
        for (std::vector<std::pair<int, double>>::iterator it = neighbors[i].begin(); it != neighbors[i].end(); ++it){
            allSim(c)=it->second;
            c++;
        }
        allProb= (1/((T*allSim).exp().sum()))*(T*allSim).exp();
        allSim.resize(0);
        // the probability to choose the label of the jth neighbor is equal to allProb(j)
        std::vector<double> cdf; //cumulative distribution function corresponding to allProb
        double sum=0;
        for (int j=0;j<allProb.size();j++){
            sum+=allProb(j);
            if (i==1){
                std::cout<<sum<<std::endl;
            }
            cdf.push_back(sum);
        }
        allProb.resize(0);
        allCDF.push_back(cdf);
        cdf.clear();
    }
}

/**@brief function that returns one of the neighbor of the input author characterized by its index in nodes
 *@details we simulate a random experiment "take a neighbor": it will take with a greater probability the nearest neighbor
 * thanks to the cdf constrcted previously
 *@param the index (an int) of an author 
 *@return the index of an author
*/

int Cluster::getMaxSim(int & index){
    // simulate a random experience to pick the neighbor
    double flip=(double) (rand()) /  (double) (RAND_MAX); //random float between 0 and 1
    std::vector<std::pair<int,double>>::iterator it= neighbors[index].begin();
    for (int ind=0;ind<allCDF[index].size();ind++){
        if (allCDF[index][ind]>=flip){
            return it->first;
        }
        it++;
    }  
    return it->first;
}

/**@brief function that updates the label
  *@details perform a label propagation, visit each node and give its label to one of its neighbor 
  *also save the update rate 
  *@param an array to know in which order we visit the nodes 
*/

void Cluster::updatelabel(int order[]){
    //need to save the rate of updates
    int nbupdate =0;
    std::set<int> visited;
    for (int j=0; j<sizeInput;j++){
        int index = order[j];
        if (visited.find(index)==visited.end()){
            int max=getMaxSim(index);
            visited.insert(index);
            visited.insert(max);
            if (label[max]!=label[index]){
                label[max]=label[index]; // give to the node max the label of the node i
                nbupdate+=1; //nb of updates +=1 update iff change of label
            }
        }
    }
    updaterate= double(nbupdate)/sizeInput;  
}

/**@brief function that create the clusters
  *@details first initialize the labels, create the CDF and until the clusters are quite stable perform a label propagation
  *create the clusters map that associates to each label a vector of Author
*/

void Cluster::createcluster(){
    initializelabel();
    getCDF();
    updaterate =1;
    int order [sizeInput];
    for (int i=0;i<sizeInput;i++){
        order [i]=i;
    }
    while (updaterate>0.1){ //while the rate of updates in the graph is greater to 1% we continue to update PB TOO SLOW TO HAVE THIS THRESHOLD
        std::random_shuffle(&order[0], &order[sizeInput]);
        updatelabel(order);
    }

    for (int v=0; v<label.size(); v++) {
        clusters[label[v]].push_back(nodesindex[v]);
    }
}

