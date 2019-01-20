# tell cmake to find Eigen & assume it is found
# we do this here as most algorithms will include it
# find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add_subdirectory (TFIDF)

add_library (engine MinHash.cpp
    tfidfinterface.cpp
    # declaration_knn.cpp
    clusteringlast.cpp
    matfac/mat_fac_test_with_database.cpp)

target_link_libraries (engine PUBLIC database)
