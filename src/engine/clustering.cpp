// based on the label propagation principle
// we have a vector of vector std::vector<Eigen::VectorXi> and a function getSim(Eigen::VectorXi vec1,Eigen::VectorXi vec2) that gives the similarity between two vectors
#include "clustering.hpp"
using std::exp;

void cluster::initializelabel(){
    for (int i=0;i<sizeInput;i++){
        label.push_back(i);
    }
}

void cluster::findneighbors(){
    for (int i=0;i<sizeInput;i++){ //for each vector find the K most similar vectors
        std::map<double,int> KmaxSim;
        std::map<int,double> KmaxNeigh;
        int el=0;
        int j=0;
        while (j<K){
            if (i!=el){
                double s= getSim(nodes[i],nodes[el]);
                KmaxSim.insert(std::pair<double,int>(s,el));
                j+=1;
                el+=1;
            }
            else {
                el+=1;
            }
        }
        double minSim=KmaxSim.begin()->first; //since the key are ordered by increasing order in a map the minimum similitude is the first key of the map
        for (int j=K;j<sizeInput;j++){
            if (i!=j){
                double s= getSim(nodes[i],nodes[j]);
                if (s>minSim){ 
                    KmaxSim.erase(minSim);
                    KmaxSim.insert(std::pair<double,int>(s,j));
                    minSim=KmaxSim.begin()->first;
                }
            }
        }
        for (std::map<double, int>::iterator k = KmaxSim.begin(); k != KmaxSim.end(); ++k){
            KmaxNeigh[k->second] = k->first;
            }
        neighbors.push_back(KmaxNeigh);
    }
}

int cluster::getMaxSim(int & i){
    Eigen::ArrayXd allSim; // vector of similarities between the ith node and all its neighbors
    Eigen::ArrayXd allProb; //vector of e^si/sum(e^si)
    std::vector<int> orderedNeigh;
    int c=0;
    //iterate over the map neighbors(i) to have an array of similarities
    for (std::map<int, double>::iterator it = neighbors[i].begin(); it != neighbors[i].end(); ++it){
        orderedNeigh.push_back(it->first);
        allSim(c)=it->second;
        c++;
    }
    allProb= (1/(T*allSim).exp().sum())*(T*allSim).exp();
    // the probability to choose the label of the jth neighbor is equal to allProb(j)
    std::vector<double> cdf; //cumulative distribution function corresponding to allProb
    double sum=0;
    for (int j=0;j<allProb.size();j++){
        sum+=allProb(j);
        cdf.push_back(sum);
    }
    // simulate a random experience to pick the neighbor
    double flip=(double) (rand()) /  (double) (RAND_MAX); //random float between 0 and 1
    for (int ind=0;ind<cdf.size();ind++){
        if (cdf[ind]>=flip){
            return orderedNeigh[ind];  
        }
    }  
}
void cluster::updatelabel(){
    //need to save the rate of updates
    int nbupdate =0;
    for (int i=0; i<sizeInput;i++ ){
        int max=getMaxSim(i);
        if (label[max]!=label[i]){
            label[max]=label[i]; // give to the node max the label of the node i
            nbupdate+=1; //nb of updates +=1 update iff change of label
        }
    }
    updaterate= nbupdate/sizeInput;
}

void cluster::createcluster( std::vector<Eigen::VectorXd> & input){
    T=1; //to be determined
    K=20; //to be determined
    nodes= input;
    sizeInput = input.size();
    findneighbors();
    initializelabel();
    updaterate =1;
    while (updaterate>0.01){ //while the rate of updates in the graph is greater to 1% we continue to update
        updatelabel();
    }
}


int main(){
    srand(time(0)); //make a seed that will be use to generate random numbers
    //don't know how to give the input of the form std::vector<Eigen::VectorXi> to the algorithm
    cluster res(input);
    std::vector <int> labelres= res.label;
    std::vector<int> listlabel; //list of all the labels
    for (int v=0; v<labelres.size(); v++) {
        if(std::find(listlabel.begin(), listlabel.end(), labelres[v]) == listlabel.end()) {
            listlabel.push_back(labelres[v]);
        }
            std::cout<<"the node "<<v<< "has label"<< labelres[v]<<std::endl;
    }
    std::cout<<"the number of clusters is"<<listlabel.size()<<std::endl; //to know how many clusters we have created

    return 0;

}