
#include "clustering2.hpp"

int cluster::most_freq(int & i){ //return the neighbor with the most popular label 
    std::vector<int> vec;
    for (int k=0;k<nodes[i].size();k++){
        vec.push_back(label[k]);
    }
    sort(vec.begin(),vec.end());
    int max_count=1;
    int res= vec[0];
    int curr_count=1;
    for (int j=1;j<vec.size();j++){
        if (vec[j]==vec[j-1]){
            curr_count++;
        }
        else {
            if (curr_count > max_count){
                max_count=curr_count;
                res=vec[j-1];
            }
            else if (curr_count==max_count){ //if max and cur equal choose randomly
                double r=(double) (rand()) /  (double) (RAND_MAX);
                if (r>=double(1)/2){
                    max_count=curr_count;
                    res=vec[j-1];
                }
            }
            curr_count=1;
        }
    }
    if (curr_count>max_count){
        max_count=curr_count;
        res=vec[vec.size()-1];
    }
    else if (curr_count==max_count){
        double r=(double) (rand()) /  (double) (RAND_MAX);
        if (r>=double(1)/2){
            max_count=curr_count;
            res=vec[vec.size()-1];
        }
    }
    return res;
}

void cluster::initlabel(){
    for (int i=0; i<sizeInput;i++){
        label.push_back(i);
    }
}

void cluster::propagate(){
    int arr [sizeInput];
    for (int i=0;i<sizeInput;i++){
        arr [i]=i;
    }
    for (int c=0;c<5;c++){ //we do 5 times the propagation (here chosen arbitrarily)
        std::random_shuffle(&arr[0], &arr[sizeInput]); //take the nodes in a random order
        std::set<int> visited;
        for (int j=0;j<sizeInput;j++){
            if (visited.find(j)==visited.end()){
                visited.insert(j);
                int ind=arr[j];
                visited.insert(ind);
                int newlabel=most_freq(ind);
                label[ind]= newlabel; //the node ind takes the most popular label among its neighbors
            }
        }  
    }
    
}

