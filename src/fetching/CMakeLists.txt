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
add_library (crawler crawler.cpp references.cpp)
target_link_libraries (crawler ${CURL_LIBRARIES})
target_link_libraries (crawler ${ZLIB_LIBRARIES})
