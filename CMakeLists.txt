# barebones project
cmake_minimum_required (VERSION 3.5)
project (realtime-recommendation)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# install pistache
add_subdirectory (libraries/pistache)

# ugh include libs
include_directories (libraries/eigen-git-mirror)
include_directories (libraries/pistache/include)
include_directories (libraries)

# add boost to include dirs
find_package (Boost 1.40 REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

# structure
add_subdirectory (src)
# target_include_directories (crawler PUBLIC "libraries")
target_include_directories (database PUBLIC "src/fetching")

add_subdirectory (tests)
target_include_directories (testcrawler PUBLIC "src/fetching")

enable_testing ()
add_test (NAME crawlertest COMMAND testcrawler)
