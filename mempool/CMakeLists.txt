include_directories(src)
add_executable(output/TestMempool example/TestMempool.cpp)
target_link_libraries(output/TestMempool gflags)