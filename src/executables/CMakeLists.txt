add_executable (crawl crawl.cpp)
target_link_libraries (crawl crawler)
target_link_libraries (crawl database)

add_executable (download_references download_references.cpp)
target_link_libraries (download_references crawler)
target_link_libraries (download_references database)

add_executable (serve serve.cpp)
target_link_libraries (serve database)
