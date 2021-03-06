#include "tfidfinterface.hpp"

TFIDF::iterator TFIDF::iterator::operator++() {
    if (cursor == parent->buffer.end())
        goto fillup;
    else if (++cursor == parent->buffer.end())
        goto fillup;
    else
        goto done;

    fillup: {
        std::vector<pEdge> copy = parent->buffer;
        parent->buffer.clear();
        for (int j = 1000; j < copy.size(); j++)
            parent->buffer.push_back(copy[j]);

        copy.clear();
        parent->update(1000);
        cursor = parent->buffer.begin();
    }

    done:
        return *this;
}

TFIDF::pEdge TFIDF::iterator::operator*() const { return *cursor; }

TFIDF::iterator TFIDF::begin() {
    iterator it(this);
    return it;
}

TFIDF::iterator TFIDF::end() {
    iterator it(this);
    return it;
}

/**@brief convert a summary in a vector of words
 *@details use the tokenizer of the boost library to convert a summary in a vector of words
 *@param a summary
 *@return a vector of words
 */

std::vector<std::string> TFIDF::textParse(const std::string &summary) {
    std::vector<std::string> vec;
    boost::tokenizer<> tok(summary);
    for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
        std::string str = *beg;
        for (int i = 0; i < str.size(); i++) {
            str[i] = std::tolower(str[i]); // put all in lowercase
        }
        vec.push_back(str);
    }
    return vec;
}

/**@brief use a parsed summary to update the Occ2d and vocab
 * @details save the number of occurences of each word for a summary
 */

void TFIDF::convertsum(const std::vector<std::string> &parsed_sum) {
    std::vector<double> OccVec(vocab.size(),
                               0); // array that stores the number of occurences of a word
    for (std::string word : parsed_sum) {
        if (vocab.find(word) ==
            vocab
                .end()) { // if it is the first time we encounter the word then insert it in the map
            vocab.insert(std::pair<std::string, int>(
                word, counter)); // a map that associates to each word an integer
            OccVec.push_back(1);
            counter++;
        } else {
            OccVec[vocab[word]] += 1;
        }
    }
    Occ2d.push_back(OccVec);
    OccVec.clear();
}

// convert Occ2d which has a not fixed size in an Eigen::MatrixXd OccMat
void TFIDF::createOccMat() {
    nrow = Occ2d.size();
    ncol = vocab.size();
    OccMat.resize(nrow, ncol);
    for (int i = 0; i < nrow; ++i) {
        Occ2d[i].resize(ncol, 0); // they all have the same size
        Eigen::Map<Eigen::VectorXd> vec(Occ2d[i].data(), Occ2d[i].size());
        OccMat.row(i) = vec;
    }
}

// create the CountDoc Eigen::MatrixXd which count for each word in how many summaries it is present
void TFIDF::createCountDoc() {
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

// compute the tfidf matrix -> weightMat
void TFIDF::calweightMat() {
    createOccMat();
    createCountDoc();
    weightMat.resize(nrow, ncol);
    Eigen::MatrixXd tf = Eigen::MatrixXd::Zero(nrow, ncol);
    Eigen::MatrixXd idf = Eigen::MatrixXd::Zero(ncol, ncol);
    for (unsigned int j = 0; j < ncol; ++j) {
        idf(j, j) = log(double(nrow) / (CountDoc(j)));
    }
    for (unsigned int i = 0; i < nrow; ++i) {
        tf.row(i) = OccMat.row(i) * (1 / OccMat.row(i).sum());
    }
    weightMat = tf * idf;
}
/**@brief do the update by pulling new summaries (up to a given threshold) and update accordingly the
  *weightMat and the buffer
*/
void TFIDF::update(int threshold) {
    for (SummariesIt::iterator it = summaries.begin(); it != summaries.end(); ++it) {
        auto itval = *it;
        if (papers.find(itval.id) == papers.end()) {
            papers.insert(itval.id);
            std::vector<std::string> parsed_abstract = textParse(itval.summary);
            convertsum(parsed_abstract);
        }

        if (papers.size() > threshold) {
            break;
        }
    }

    calweightMat();
    int i = 0;
    for (std::unordered_set<std::string>::iterator it1 = papers.begin(); it1 != papers.end();
         it1++) {
        int j = 0;
        for (std::map<std::string, int>::iterator it2 = vocab.begin(); it2 != vocab.end(); it2++) {
            /*fill the buffer object with pEdge objects composed of a word, a Paper and the
             * corresponding tfidf coefficient*/
            if (weightMat(i,j)>0){
                buffer.push_back(std::make_tuple(it2->first, Paper(*it1), weightMat(i, j)));
            }
            j++;
        }
        i++;
    }
}

SummariesIt::SummariesIt(std::string sdata) : sdata(sdata), driver(sdata), sAccess(sdata) {
    // SummaryAccessor sAccess(sdata);
    auto allKeys = sAccess.getKeys();
    std::set<std::string> seen;

    for (auto paper : allKeys)
        seen.insert(paper.id);
    
    allKeys.clear();
    for (auto paper_s : seen)
        allKeys.push_back(Paper(paper_s));
    
    this->pKeys = allKeys;
}

SummariesIt::iterator SummariesIt::iterator::operator++() {
    this->cursor = this->cursor + 1;
    return *this;
}

Paper SummariesIt::iterator::operator*() const {
    Paper p = this->parent->pKeys[this->cursor];
    std::string summ = this->parent->sAccess.getSummary(p);
    p.summary = summ;
    return p;
}

SummariesIt::iterator SummariesIt::begin() { return iterator(this, 0); }
SummariesIt::iterator SummariesIt::end() { return iterator(this, pKeys.size()); }
