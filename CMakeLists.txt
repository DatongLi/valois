cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(mempool/src threadpool/src net/src .)

add_executable(mempool/output/TestMempool mempool/example/TestMempool.cpp)

link_libraries(pthread)
add_executable(threadpool/output/TestThreadpool threadpool/example/TestThreadpool.cpp)

add_subdirectory(${CMAKE_BINARY_DIR}/thirdparty)
add_executable(output/gtest_test test/test.cpp test/unittest/gtest_test.cpp)
target_link_libraries(output/gtest_test gtest_main gtest)
add_test(NAME output/gtest_test COMMAND output/gtest_test)