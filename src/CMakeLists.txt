add_subdirectory (database)

add_subdirectory (fetching)
target_include_directories (crawler PUBLIC "database")

add_subdirectory (engine)
target_include_directories (engine PUBLIC "database")

add_subdirectory (server)
target_include_directories (serve PRIVATE "database")

# must be last as it depends on libraries defined above
add_subdirectory (executables)
target_include_directories (crawl PRIVATE "fetching" "database")
target_include_directories (download_references PRIVATE "fetching" "database")
target_include_directories (minhash PRIVATE "database" "engine")
target_include_directories (cluster PRIVATE "database" "engine")
target_include_directories (tfidf PRIVATE "database" "engine")
target_include_directories (runmf PRIVATE "database" "engine")
# target_include_directories (runknn PRIVATE "database" "engine")
