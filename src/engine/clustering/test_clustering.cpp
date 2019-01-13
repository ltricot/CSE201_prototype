#include "clustering.hpp"


std::vector<Eigen::VectorXd> genInput(){
    std::vector<Eigen::VectorXd> res;
    for (int i=0;i<100;i++){
        Eigen::VectorXd vec;
        vec.resize(5);
        vec= (Eigen::VectorXd::Random(5).array()+1)*10;
        vec=vec.array().floor();
        res.push_back(vec); 
    }
    return res;
}

int main(){
    srand(time(0)); //make a seed that will be use to generate random numbers
    std::vector<Eigen::VectorXd> input=genInput();
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
