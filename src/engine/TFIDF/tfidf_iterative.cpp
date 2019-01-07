#include "tfidf_iterative.hpp"
#include "boost_1_69_0/boost/tokenizer.hpp"
#include "boost_1_69_0/boost/algorithm/string.hpp"
#include <clocale>
#include "json.hpp"

using namespace nlohmann;
using namespace tfidf;

//convert a string in a vector of words
std::vector<std::string> textParse(const std::string & summary) { 
		std::vector<std::string> vec;
		boost::tokenizer<> tok(summary);
		for(boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++ beg) {
			std::string str= *beg;
			for(int i=0; i<str.size(); i++) {
      			str[i] = std::tolower(str[i]); //put all in lowercase
    		}
		    vec.push_back(str);
		}
		return vec;
}

void update(const std::vector<std::string> & parsed_doc){
    std::vector<int> OccVec(vocab.size(),0) //array that stores the number of occurences of a word
    for (std::string word : parsed_doc) {
        if ( vocab.find(word) == vocab.end() ) { //if it is the first time we encounter the word then insert it in the map
		    vocab.insert(std::pair<std::string, int>(word,counter)); // a map that associates to each word an integer
            OccVec.pushback(1); 
		    counter++;
	    }	
        else {
            OccVec[vocab[word]]+=1;
        }
    }
    Occ2d.pushback(OccVec);
    OccVec.clear();
}


void reader(int argc, char *argv[]) {
    assert(argc == 2);
    std::ifstream infile(argv[1]);
    std::string line;

    while(std::getline(infile, line)) {
        auto j = json::parse(line);
        for(auto& el : j.items()) {
            std::string abstract=el.value()[0];
            std::vector<std::string> parsed_abstract= textParse(abstract);
            update(parsed_abstract);
        }
    }
}

void createOccMat(){
    nrow = Occ2d.size()
    ncol = vocab.size()
    OccMat.resize(nrow, ncol);
    for (int i = 0; i < nrow; ++i) {
            Occ2d[i].resize(ncol,0); //they all have the same size
			OccMat.row(i)=Occ2d[i];
	}
}

void createCountDoc() {
	Eigen::MatrixXd dataMat(OccMat); //copy OccMat
	CountDoc = Eigen::VectorXd::Zero(ncol);
	for (unsigned int i = 0; i <nrow; ++i) {
		for (unsigned int j = 0; j < ncol; ++j) {
			if (dataMat(i,j) >= 1) {// only keep 1 and 0
				dataMat(i,j) = 1;
			} //if the word appears in the doc put 1 otherwise : 0
		}
	}	
	for (unsigned int i = 0; i <nrow; ++i) {
		CountDoc += dataMat.row(i); //sum up the columns
	}
	dataMat.resize(0,0);
}

void calweightMat(int argc, char *argv[]) {
    reader(argc,argv);
    //when the iterative part is over
    createOccMat();
	createCountDoc();
    weightMat.resize(nrow, ncol);
	Eigen::MatrixXd tf = Eigen::MatrixXd::Zero(nrow,ncol);
	Eigen::MatrixXd idf = Eigen::MatrixXd::Zero(ncol,ncol);
	for (unsigned int j = 0; j < ncol; ++j) {
		idf(j,j)= log(nrow / (CountDoc(j)));
	}
	for (unsigned int i=0; i<nrow;++i) {
		tf.row(i)= OccMat.row(i)*(1/OccMat.row(i).sum());
	}
	weightMat = tf * idf; 	

}

int main(int argc, char *argv[]) {
    tfidf ins(argc, argv);
    Eigen::MatrixXd mat = ins.weightMat;
}
