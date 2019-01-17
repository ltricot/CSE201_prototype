# get that curl
find_package (CURL REQUIRED)
if (CURL_FOUND)
    include_directories (${CURL_INCLUDE_DIR})
else (CURL_FOUND)
    message (FATAL_ERROR "no curl we done hon")
endif (CURL_FOUND)

# yo where zlib at
find_package (ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories (${ZLIB_INCLUDE_DIR})
else (ZLIB_FOUND)
    message (FATAL_ERROR "no zlib :(")
endif (ZLIB_FOUND)

# add crawler code as a library
# PRIVATE means those libraries are used in the implementation
# and user code has no need to know about them
add_library (crawler crawler.cpp quickrefs.cpp)
target_link_libraries (crawler PRIVATE ${CURL_LIBRARIES})
target_link_libraries (crawler PRIVATE ${ZLIB_LIBRARIES})
target_link_libraries (crawler PRIVATE stdc++fs)
