add_library (database driver.cpp Matrix.cpp Reader.cpp Vectors.cpp)
target_link_libraries (database PUBLIC stdc++fs)
