add_library (client client.cpp tools.cpp)

# get that curl
find_package (CURL REQUIRED)
if (CURL_FOUND)
    include_directories (${CURL_INCLUDE_DIR})
else (CURL_FOUND)
    message (FATAL_ERROR "no curl we done hon")
endif (CURL_FOUND)

# link that curl mmmmmm
target_link_libraries(client PUBLIC ${CURL_LIBRARIES})

add_executable (testclient learn.cpp)
target_link_libraries (testclient client)

# this be no joke
add_executable (serve server8.cpp)
target_link_libraries (serve pistache_static)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(serve Threads::Threads)

target_link_libraries (serve database)
