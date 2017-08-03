cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")
link_libraries(pthread)

include_directories(.)

add_subdirectory(${CMAKE_BINARY_DIR}/thirdparty)
add_subdirectory(mempool)
add_subdirectory(threadpool)
add_subdirectory(net)

add_executable(output/test/gtest_test test/test.cpp test/unittest/gtest_test.cpp)
target_link_libraries(output/test/gtest_test gtest_main gtest)
add_test(NAME output/test/gtest_test COMMAND output/test/gtest_test)