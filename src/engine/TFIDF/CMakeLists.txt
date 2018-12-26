add_library (tfidf tfidf.cpp)
target_link_libraries (tfidf Eigen3::Eigen)

# add boost to include dirs
find_package (Boost 1.40 REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

add_executable (tfidf_arxiv tfidf_arxiv.cpp)
target_link_libraries (tfidf_arxiv tfidf)
target_link_libraries (tfidf_arxiv PUBLIC ${Boost_LIBRARIES})
