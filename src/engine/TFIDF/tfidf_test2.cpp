
#include "tfidf2.hpp"
int main(){
    TFIDF  tfidf;
    TFIDF::iterator iter(&tfidf);
    for (iter=tfidf.begin();iter!=tfidf.end();++iter){
        std::cout<<std::get<0>(*iter)<<"|"<<std::get<1>(*iter)<<"|"<<std::get<2>(*iter)<<std::endl;
    }

}