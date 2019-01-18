add_subdirectory (database)
add_subdirectory (fetching)
add_subdirectory (engine)

target_include_directories (crawler PUBLIC "database")

# must be last as it depends on libraries defined above
add_subdirectory (executables)
target_include_directories (crawl PUBLIC "fetching" "database")
target_include_directories (download_references PUBLIC "fetching" "database")
target_include_directories (serve PUBLIC "database")
