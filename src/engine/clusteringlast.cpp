// based on the label propagation principle
#include "clusteringlast.hpp"
using std::exp;



int cluster::T =2;

void cluster::initializelabel(){
    for (int i=0;i<sizeInput;i++){
        label.push_back(i);
    }
}

void cluster::findneighbors(std::vector<Friends> & similarities){
    
    for (std::vector<Friends>::iterator it=similarities.begin();it!=similarities.end();it++){
        std::vector<Author>::iterator it1 = std::find(nodes.begin(),nodes.end(),std::get<0>(*it));
        std::vector<Author>::iterator it2 = std::find(nodes.begin(),nodes.end(),std::get<1>(*it));

        if (it1== nodes.end()){
            nodes.push_back(std::get<0>(*it));
            neighbors.push_back(std::map<Author,double>());  //do another map
            int pos1=nodes.size()-1;
        }
        else{
            int pos1=std::distance(nodes.begin(),it1);
        }
        if (it2==nodes.end()){
            nodes.push_back(std::get<1>(*it));
            neighbors.push_back(std::map<Author,double>());
            int pos2=nodes.size()-1;
        }
        else {
            int pos2=std::distance(nodes.begin(),it2);
        }
        neighbors[pos1].insert(std::pair<int,double>(pos2,std::get<2>(*it)));
        neighbors[pos2].insert(std::pair<int,double>(pos1,std::get<2>(*it)));
    }
}

void cluster::getCDF(){
    for (int i=0;i<sizeInput;i++){
        Eigen::ArrayXd allSim; // vector of similarities between the ith node and all its neighbors
        Eigen::ArrayXd allProb; //vector of e^si/sum(e^si)
        allSim.resize(neighbors[i].size());
        allProb.resize(neighbors[i].size());
        int c=0;
        //iterate over the map neighbors(index) to have an array of similarities
        for (std::map<int, double>::iterator it = neighbors[i].begin(); it != neighbors[i].end(); ++it){
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


int cluster::getMaxSim(int & index){
    // simulate a random experience to pick the neighbor
    double flip=(double) (rand()) /  (double) (RAND_MAX); //random float between 0 and 1
    std::map<int,double>::iterator it= neighbors[index].begin();
    for (int ind=0;ind<allCDF[index].size();ind++){
        if (allCDF[index][ind]>=flip){
            return it->first;
        }
        it++;
    }  
    return it->first;
}

void cluster::updatelabel(int order[]){
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


void cluster::createcluster(){
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
        clusters[label[v]].push_back(nodes[v]);
    }
}

