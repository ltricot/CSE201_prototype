add_executable (crawl crawl.cpp)
target_link_libraries (crawl crawler)
target_link_libraries (crawl database)

add_executable (download_references download_references.cpp)
target_link_libraries (download_references crawler)
target_link_libraries (download_references database)

add_executable (minhash runMinHash.cpp)
target_link_libraries (minhash database engine stdc++fs)

add_executable (cluster cluster.cpp)
target_link_libraries (cluster database engine stdc++fs)

add_executable (tfidf runtfidf.cpp)
target_link_libraries (tfidf database engine stdc++fs)

add_executable (runmf runMF.cpp)
target_link_libraries (runmf database engine stdc++fs)

add_executable (runknn runKNN.cpp)
target_link_libraries (runknn engine stdc++fs)

# add_executable (serve serve.cpp)
# target_link_libraries (serve database)
