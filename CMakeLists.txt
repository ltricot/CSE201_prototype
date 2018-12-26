# barebones project
cmake_minimum_required (VERSION 3.5)
project (realtime-recommendation)

# structure
add_subdirectory (src)
target_include_directories (crawler PUBLIC "libraries")

add_subdirectory (tests)
target_include_directories (testcrawler PUBLIC "src/fetching")

enable_testing ()
add_test (NAME crawlertest COMMAND testcrawler)
