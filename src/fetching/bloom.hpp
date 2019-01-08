#include <bitset>
#include <string>
#include <vector>


template <class Hashable> class Bloom {
    /*TO DO:
    - port it to personal github and make a general implementation
        - add the formulas for calculating n, k, m, p and describe it well
    - finish the docs below
    - start coding!!!
    */
    /*
    * Data structure that allows us to check membership (and insert) in less than linear time.
    *
    * It is made as a template as the only assumption made on the type of information stored 
    * in the Bloom filter is that one can hash it efficiently. The below public methods are made
    * for all who simply wish to interact with the data structure, while not being bothered by
    * the details of it. 
    */   
    public:
    /*
    * Public variables:
    *       
    * Public methods:
    *       - ``Bloom(std::string path, int bitsize)``: simply a constructor, it is subject to change when I start coding.
    *    
    *       - ``bool seen(Hashable info)``: returns False if the ``Hashable info` is not in the Bloom filter, 
    *           and returns True if it is.
    *       - ``bool add(Hashable info)``: adds the `Hashable info`` to the Bloom filter.
    *       - ``void reset()``: as the name suggest it resets the Bloom filter to an empty state - this will not 
    *           delete any saved files just clears the filter in the C++ (i.e. re-initializes it)
    *           ATTENTION - THIS IS NOT A DESTRUCTOR
    *       - ``Bloom * import(std::string path)``: reads an existing Bloom filter structure from a data file located at 
    *           the ``std::string path`` and returns it as a pointer to a ``Bloom`` object.
    *       - ``void export(std::string path)``: exports the Bloom object to a ``.dat`` file located at the ``std::string path``    
    *           location.
    *       - ``void setPath(std::string path)``: a standard setter method for the path location.
    *       - ``std::string getPath()``: a standard getter method for the path variable.
    *       - ``~Bloom()``: your standard destructor class that takes care of deallocating memory.
    */
    Bloom(std::string path, int bitsize);
    Bloom(std::string path);
    Bloom(int bitsize);
    Bloom();
    bool seen(Hashable info);
    bool add(Hashable info);
    void reset();
    Bloom * importBloom(std::string path);
    void exportBloom(std::string path);
    void setPath(std::string path);
    std::string getPath();
    ~Bloom();
    std::string DoYouHash; 
    //NOTE: THE PRIVATE PART IS UNFINISHED AND SUBJECT TO CHANGE
    private:
    /*
    * Private variables:
    *       - ``std::string path``: stores the path (absolute) location of where the Bloom filter (byteset should be stored.     
    *           The value defaults to NULL if it is not provided in the constructor.
    *       - ``int hashers``: the amount of hash functions used, initialized in this project to 23.
    *       - ``bset``: the current bitset that stores the Bloom filter. The number of bits was calculated by
    *           https://hur.st/bloomfilter/
    *       - ``int bitsize``: sets the size of the biteset that will be used to store the filter. For this project leave it
    *           empty to have it done for you.
    *       
    * Private methods:
    *       - ``int[hashers] * hash(Hashable info)``: returns array containing the hashes of the (Hashable info) computed by
    *          the ``hashers`` different hash functions. Basically will tell us what bits to set in the bitset.
    *       - ``int[hashers] getBits(std::vector<unsigned long int>  locs)``: returns a pointer to an array of bits (1s and 0s) 
    *           located in ``bset`` at the locations specified in ``locs``.
    *       - ``void setBits(std::vector<unsigned long int> locs)``: sets the bits located in ``bset``
    *           at the locations specified in ``locs`` to 1. We only support setting to 1 as that is 
    *           all we need in a Bloom filter.
    */
    std::string path;
    int hashers;
    int bitsize;
    // std::bitset bset(bitsize);

    // int[hashers] * hash(Hashable info);
    // int[hashers] * getBits(std::vector<unsigned long int>  locs);
    void setBits(std::vector<unsigned long int> locs);
};
