# Currently mostly commented as many of the files referenced have
# not been created yet. We must test cmake ASAP.

# barebones project
cmake_minimum_required (VERSION 3.5)
project (realtime-recommendation)

# those files do not exist yet
#
# add_executable(crawl src/fetching/crawl.cpp)
# add_executable(engine src/engine/engine.cpp)

# tell cmake where to find zlib and which executable it is relevant to
# we want to crash in case zlib is not found, so no ``if`` construct
#
# find_package (ZLIB REQUIREd)
# include_directories (${ZLIB_INCLUDE_DIRS})
# target_link_libraries (crawl ${ZLIB_LIBRARIES})

# tell cmake where to find Eigen and which executable it is relevant to
#
# find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# add_executable (engine src/engine/engine.cpp)
# target_link_libraries (engine Eigen3::Eigen)

# install (TARGETS crawl DESTINATION bin)
# install (TARGETS engine DESTINATION bin)

add_executable (testcrawl tests/crawlertest.cpp)
include_directories ("libraries")
