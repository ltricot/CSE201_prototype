add_subdirectory (fetching)
add_subdirectory (engine)
# add_subdirectory (database)

# must be last as it depends on libraries defined above
add_subdirectory (executables)
target_include_directories (crawl PUBLIC "fetching" "database")
