#include "tfidf.hpp"

void tfidf::createVocabList() {
    int i = 0;
    for (std::vector<std::string> document : SetofDocs) {
        for (std::string word : document) {
            if (vocab.find(word) == vocab.end()) { // if it is the first time we encounter the word
                                                   // then insert it in the map
                vocab.insert(std::pair<std::string, int>(
                    word, i)); // a map that associates to each word an integer
                i++;
            }
        }
    }
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

Eigen::VectorXd tfidf::countOccDoc(const std::vector<std::string> &doc) {
    Eigen::VectorXd res =
        Eigen::VectorXd::Zero(vocab.size()); // create an array of size vocab full of zero

    /*return a vector whose coeff i correspond to the number of occurences in the doc of
    the word associated to the integer i in vocab map*/
    for (std::string word : doc) {
        int i = vocab[word];
        res(i) += 1;
    }
    return res;
}

void tfidf::createOccMat() {
    std::vector<Eigen::VectorXd> vec;
    for (std::vector<std::string> document : SetofDocs) // iterate over the docs
    {
        vec.push_back(countOccDoc(document)); // compute the counting occurences vector for a doc
                                              // and insert it in the matrix OccMat
    }
    ncol = vec[0].size(); // size of a vector for one document -> size of vocablist
    nrow = vec.size();    // nb of documents
    OccMat.resize(nrow, ncol);
    for (int i = 0; i < nrow; ++i) {
        OccMat.row(i) = vec[i];
    }
    SetofDocs.clear(); // release memory
}

void tfidf::createCountDoc() {

    Eigen::MatrixXd dataMat(OccMat); // copy OccMat
    CountDoc = Eigen::VectorXd::Zero(ncol);
    for (unsigned int i = 0; i < nrow; ++i) {
        for (unsigned int j = 0; j < ncol; ++j) {
            if (dataMat(i, j) >= 1) { // only keep 1 and 0
                dataMat(i, j) = 1;
            } // if the word appears in the doc put 1 otherwise : 0
        }
    }
    for (unsigned int i = 0; i < nrow; ++i) {
        CountDoc += dataMat.row(i); // sum up the columns
    }
    dataMat.resize(0, 0);
}

/* This is where you need to take advantage of Eigen.
 * Find a way to reduce your loops to matrix operations and call the corresponding
 * Eigen methods on your matrices / vectors.
 *
 * Eigen does the looping itself and does it much (much!) faster.
 */

/*void tfidf::calweightMat() {
        createVocabList();
        createOccMat();
        createCountDoc();

        weightMat.resize(nrow, ncol);
        for (unsigned int i = 0; i < nrow; ++i)
        {
                for (unsigned int j = 0; j < ncol; ++j)
                {
                        double tf = OccMat(i,j) / (OccMat.row(i).sum()); //compute the term
frequency double idf = log(nrow / (CountDoc(j)) ); //compute the inverse doc frequency
                        weightMat(i,j) = tf * idf; // TF-IDF equation
                }

        }

}*/

void tfidf::calweightMat() {
    createVocabList();
    createOccMat();
    createCountDoc();
    weightMat.resize(nrow, ncol);
    Eigen::MatrixXd tf = Eigen::MatrixXd::Zero(nrow, ncol);
    Eigen::MatrixXd idf = Eigen::MatrixXd::Zero(ncol, ncol);
    for (unsigned int j = 0; j < ncol; ++j) {
        idf(j, j) = log(nrow / (CountDoc(j)));
    }
    for (unsigned int i = 0; i < nrow; ++i) {
        tf.row(i) = OccMat.row(i) * (1 / OccMat.row(i).sum());
    }
    weightMat = OccMat * idf;
}
