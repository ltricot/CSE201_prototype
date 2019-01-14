# barebones project
cmake_minimum_required (VERSION 3.5)
project (realtime-recommendation)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# ugh dependencies
include_directories (libraries/eigen-git-mirror)

# structure
add_subdirectory (src)
target_include_directories (crawler PUBLIC "libraries")

add_subdirectory (tests)
target_include_directories (testcrawler PUBLIC "src/fetching")

enable_testing ()
add_test (NAME crawlertest COMMAND testcrawler)
