# tell cmake to find Eigen & assume it is found
# we do this here as most algorithms will include it
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory (TFIDF)
