#include "tfidfinterface.hpp"

TFIDF::iterator TFIDF::iterator::operator++(){
    if (cursor == buffer.end())
        goto fillup;
    else if (++cursor == buffer.end())
        goto fillup;
    else
        goto done;

    fillup: {
        std::vector<pEdge> copy = buffer;
        buffer.clear();
        for (j=1000;j<copy.size();j++){
            buffer.push_back(copy[j]);
        }
        copy.clear();
        parent->update(1000);
        cursor = buffer.begin();
    }
    done: {
        return *this;
    }
}

pEdge TFIDF::iterator::operator*() const{
        return *cursor;
}

TFIDF::iterator TFIDF::begin() {
    iterator it(this, true);
    return it;
}

TFIDF::iterator TFIDF::end() {
    iterator it(this);
    return it;
}

//convert a string in a vector of words
std::vector<std::string> TFIDF::textParse(const std::string & summary) { 
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

void TFIDF::convertsum(const std::vector<std::string> & parsed_sum){
    std::vector<double> OccVec(vocab.size(),0); //array that stores the number of occurences of a word
    for (std::string word : parsed_sum) {
        if ( vocab.find(word) == vocab.end() ) { //if it is the first time we encounter the word then insert it in the map
		    vocab.insert(std::pair<std::string, int>(word,counter)); // a map that associates to each word an integer
            OccVec.push_back(1); 
		    counter++;
	    }	
        else {
            OccVec[vocab[word]]+=1;
        }
    }
    Occ2d.push_back(OccVec);
    OccVec.clear();
}

void TFIDF::createOccMat(){
    nrow = Occ2d.size();
    ncol = vocab.size();
    OccMat.resize(nrow, ncol);
    for (int i = 0; i < nrow; ++i) {
            Occ2d[i].resize(ncol,0); //they all have the same size
            Eigen::Map<Eigen::VectorXd> vec(Occ2d[i].data(),Occ2d[i].size()) ;
			OccMat.row(i)=vec;
	}
}

void TFIDF::createCountDoc() {
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

void TFIDF::calweightMat(int argc, char *argv[]) {
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

void TFIDF::update(int &threshold){
    Summaries summaries;
    for (Summaries::iterator it=summaries.begin();it!=summaries.end();it++){
            if (papers.find(*it->id)==papers.end()) {  
              papers.insert(*it->id);
              std::vector<std::string> parsed_abstract= textParse(*it->summary));
              convertsum(parsed_abstract);
            }
            if (papers.size()>threshold){        
                break;
            }    
        }
        calweightMat();
    int i=0;
    for (std::map<std::string,int>::iterator it1=vocab.begin();i!=vocab.end();i++){
        int j=0;
        for (std::unorderedset<Paper>::iterator it2=papers.begin();j!=papers.end();j++){
            buffer.push_back(std::make_tuple(*it1->first,Paper(*it2),weightMat(i,j))); 
            j++;        
        }
        i++;
    }
}



