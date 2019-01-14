#include "clustering2.hpp"



std::vector<Eigen::VectorXd> genGraph(){ //generate a graph: a node has a specific signature characterized by 3 integers
    std::vector<Eigen::VectorXd> res;
    for (int i=0;i<1000;i++){
        Eigen::VectorXd vec;
        vec.resize(3);
        vec= (Eigen::VectorXd::Random(3).array()+1)*100;
        vec=vec.array().floor();
        res.push_back(vec); 
    }
    return res;
}

int getSim(Eigen::VectorXd & vec1, Eigen::VectorXd & vec2) { //get the similarity between two nodes
    int res=0;
    for (int k=0; k<vec1.size(); k++){
        if (vec1(k)==vec2(k)){
            res=1;
            break;
        }
    }
    return res;
}

std::vector<std::vector<int>> genInput(std::vector<Eigen::VectorXd> & graph){ //generate the input for the clustering ie for each node create a vector of neighbors (two nodes are neighbors if their similarity is one)
    std::vector<std::vector<int>> res;
    for (int i=0; i<graph.size(); i++){
        std::vector<int> tmp;
        for (int j=0; j<graph.size();j++){
            if (i!=j){
                if (getSim(graph[i],graph[j])==1){
                    tmp.push_back(j);
                }
            }
        }
        res.push_back(tmp);
    }
    return res;
}

int main(){
    srand(time(0)); //make a seed that will be use to generate random numbers
    std::vector<Eigen::VectorXd> graph=genGraph();
    std::vector<std::vector<int>> input = genInput(graph);
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