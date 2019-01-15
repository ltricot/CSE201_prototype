// based on the label propagation principle
// we have a vector of vector std::vector<Eigen::VectorXi> and a function getSim(Eigen::VectorXi vec1,Eigen::VectorXi vec2) that gives the similarity between two vectors
#include "clusteringlast.hpp"
using std::exp;
#include <random>


double getSim(Eigen::VectorXd & vec1, Eigen::VectorXd & vec2) {
    double res=0;
    for (int k=0; k<vec1.size(); k++){
        if (vec1(k)==vec2(k)){
            res+=1;
        }
    }
    return double(res)/vec1.size();
}

int cluster::T =2;

void cluster::initializelabel(){
    for (int i=0;i<sizeInput;i++){
        label.push_back(i);
    }
}

void cluster::findneighbors(){
    for (int i=0;i<sizeInput;i++){ //for each vector find the neighbors
        std::map<int,double> NeighSim;
        for (int j=0;j<sizeInput;j++){
            if (i!=j){
                double s= getSim(nodes[i],nodes[j]);
                if (s>0){ // here we can also give a threshold above which it is a neighbor but be carefull may raise an exception in case it is empty
                    NeighSim.insert(std::pair<int,double>(j,s));
                }
            }
        }
        neighbors.push_back(NeighSim);
        NeighSim.clear();
    }
}

void cluster::getCDF(){
    for (int i=0;i<sizeInput;i++){
        Eigen::ArrayXd allSim; // vector of similarities between the ith node and all its neighbors
        Eigen::ArrayXd allProb; //vector of e^si/sum(e^si)
        allSim.resize(neighbors[i].size());
        allProb.resize(neighbors[i].size());
        std::vector<int> orderedNeigh;
        int c=0;
        //iterate over the map neighbors(index) to have an array of similarities
        for (std::map<int, double>::iterator it = neighbors[i].begin(); it != neighbors[i].end(); ++it){
            allSim(c)=it->second;
            orderedNeigh.push_back(it->first);
            c++;
        }
        orderedNEIGH.push_back(orderedNeigh);
        orderedNeigh.clear();
        allProb= (1/((T*allSim).exp().sum()))*(T*allSim).exp();
        allSim.resize(0);
        // the probability to choose the label of the jth neighbor is equal to allProb(j)
        std::vector<double> cdf; //cumulative distribution function corresponding to allProb
        double sum=0;
        for (int j=0;j<allProb.size();j++){
            sum+=allProb(j);
            cdf.push_back(sum);
        }
        allProb.resize(0);
        allCDF.push_back(cdf);
        cdf.clear();
    }
}
int cluster::getMaxSim(int & index){
    std::vector<int> orderedNeigh = orderedNEIGH[index];
    std::vector<double> cdf= allCDF[index];
    // simulate a random experience to pick the neighbor
    double flip=(double) (rand()) /  (double) (RAND_MAX); //random float between 0 and 1
    for (int ind=0;ind<cdf.size();ind++){
        if (cdf[ind]>=flip){
            cdf.clear();
            int b=orderedNeigh[ind];
            orderedNeigh.clear();
            return b;  
        }
    }  
    int a= cdf.size()-1;
    cdf.clear();
    int b=orderedNeigh[a];
    orderedNeigh.clear();
    return b;
}

void cluster::updatelabel(){
    //need to save the rate of updates
    int nbupdate =0;
    std::vector<int> unvisited;
    for (int i=0;i<sizeInput;i++){
        unvisited.push_back(i);
    }
    std::random_shuffle(unvisited.begin(),unvisited.end());
    std::set<int> visited;
    for (int j=0; j<sizeInput;j++){
        int index=unvisited[j];
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


void cluster::createcluster( std::vector<Eigen::VectorXd> & input){
    nodes= input;
    sizeInput = input.size();
    
    findneighbors();
    initializelabel();
    getCDF();
    updaterate =1;
    while (updaterate>0.1){ //while the rate of updates in the graph is greater to 1% we continue to update PB TOO SLOW TO HAVE THIS THRESHOLD
        updatelabel();
        std::cout<<updaterate<<std::endl;
    }
}

