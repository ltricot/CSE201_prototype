#include "tfidf.hpp"

void tfidf::createVocabList() {
	std::set<std::string> AllWords;
	for (std::vector<std::string> document : SetofDocs) {//iterate over the documents in SetofDocs
	
		for (std::string word : document) { //iterate over the words in the document
			AllWords.insert(word); //insert all the words in AllWords
		} 
	}
	/*create VocabList by removing all the repetitions in the set AllWords*/
	std::copy(AllWords.begin(), AllWords.end(), std::back_inserter(vocabList)); 
}

/* A small comment concerning complexity:
 * Inside the loop over each word is an implicit loop over the vocabList to find the word's index.
 * This makes it so the complexity of this function is O(nm), where n is the document length and
 * m is the length of the vocabList.
 *
 * A solution to this would be to use a map from words to indices instead of a std::vector to
 * store the vocabList, which would make the complexity O(n). One can also iterate over a map's
 * keys so you wouldn't lose functionality.
 */
Eigen::VectorXd tfidf::countOccDoc(const std::vector<std::string> & doc) {
	Eigen::VectorXd res = Eigen::VectorXd::Zero(vocabList.size()); //create an array of size VocabList full of zero
	
	for (std::string word : doc) { //iterate over the words in the input document
		size_t i = std::find(vocabList.begin(), vocabList.end(), word) - vocabList.begin(); //the index word in doc
		if (i < vocabList.size()) 
			res(i) += 1; //add one occurence of the word 
	}

	return res; 
	/*return a vector whose coeff i correspond to the number of occurences in the doc of 
	the word at index i in vocabList*/
}

void tfidf::createOccMat() {
	std::vector<Eigen::VectorXd> vec;
	for (std::vector<std::string> document : SetofDocs) //iterate over the docs
	{
		vec.push_back(countOccDoc(document)); //compute the counting occurences vector for a doc and insert it in the matrix OccMat
		//numOfTerms.push_back(it->size());
		//it->clear();
	}
	ncol = vec[0].size(); //size of a vector for one document -> size of vocablist
	nrow = vec.size(); //nb of documents 
	OccMat.resize(nrow, ncol);
	for (int i = 0; i < nrow; ++i)
		{
			OccMat.row(i) = vec[i]; 
		}
	SetofDocs.clear(); // release memory
}

void tfidf::createCountDoc() {
	Eigen::MatrixXd dataMat(OccMat); //copy OccMat
	CountDoc.resize(ncol);
	for (unsigned int i = 0; i != nrow; ++i) {
		for (unsigned int j = 0; j != ncol; ++j) {
			if (dataMat(i,j) > 1) // only keep 1 and 0
				dataMat(i,j) = 1; //if the word appears in the doc put 1 otherwise : 0
		}
		CountDoc += dataMat.row(i); //sum up the line
	}
	dataMat.resize(0,0);
}

/* This is where you need to take advantage of Eigen.
 * Find a way to reduce your loops to matrix operations and call the corresponding
 * Eigen methods on your matrices / vectors.
 * 
 * Eigen does the looping itself and does it much (much!) faster.
 */
void tfidf::calweightMat() {
	createVocabList();
	createOccMat();
	createCountDoc();

	weightMat.resize(nrow, ncol);
	for (unsigned int i = 0; i != nrow; ++i)
	{
		for (unsigned int j = 0; j != ncol; ++j)
		{
			double tf = OccMat(i,j) / (OccMat.row(i).sum()); //compute the term frequency
			double idf = log((double)nrow / (CountDoc(j)) ); //compute the inverse doc frequency
			weightMat(i,j) = tf * idf; // TF-IDF equation
		}
	}
}
