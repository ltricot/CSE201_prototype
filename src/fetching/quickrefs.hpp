#include <fstream>
#include <string>

#include "primitives.hpp"


// typedef std::pair<Paper, Paper> Reference;

/** @brief Massive PDF downloader component.
 *  
 * @details Downloads the pdfs from s3, somewhere 
 * where arxiv stores data massively. Necessary 
 * because arxiv blocks us after the download of 
 * ~1000 single pdfs over a small time period.
 *  
 */
class Archive {
    private:

    std::string temp_pdf_folder; 
    std::string s3path, graph;
    /** @brief launches the download of .tar pdf files 
     */
    void download(); 
    /** @brief decompresses the .tar pdf files 
     */
    void decompress();

    public:

    /** @brief Constructor of the Archive objects
     * 
     * @param s3path name of the archive we will 
     * download from
     * @param graph name of the database directory
     * we will write into 
     */ 
    Archive(std::string s3path, std::string graph);

    void run(); 
};

/** @brief System of extraction of references.
 * 
 * @details an object of the class Extractor is an iterator 
 * pattern which iterates on the references produced. It 
 * represents an archive stored in s3. We proceed to a 
 * pattern matching over the text of the pdf concerned. 
 * This is done via the use of a function called findRegex 
 * which matches regular expressions in the text given.
 * The regular expression we search for is an arxiv reference,
 * which quotes the arxiv id of the paper referenced. Its format
 * is the one described here : https://arxiv.org/help/arxiv_identifier.
 * The format of ids has changed in 2007, and we made the choice
 * to only match ids dating from 2007 and onwards.
 * 
 */ 


class Extractor { 
    private:

    std::vector<Reference> references;

    public:


    /** @brief Constructor of the Extractor objets 
     * which represent the flow of extraction of a pdf.
     * 
     * @param fpath path to the pdf we want to extract
     */ 
    Extractor(std::string fpath); 

    std::vector<Reference>::iterator begin() { return references.begin(); }
    std::vector<Reference>::iterator end() { return references.end(); }
};


/** @brief binding towards external code
 * 
 * @details receives a reference towards 
 * an opened pdf file. Does that by calling 
 * the function extractText from the external
 * code. 
 * 
 * @return the text of the pdf 
 */
// open ifstream before and close after
std::string pdfToText(std::ifstream &pdf);

