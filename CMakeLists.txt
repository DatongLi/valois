cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

link_libraries(pthread)

include_directories(.)

if(POLICY CMP0037)
    cmake_policy(SET CMP0037 OLD)
endif()

add_subdirectory(thirdparty)
link_libraries(glog)
#set(gflags_DIR thirdparty/gflags)
#find_package(gflags COMPONENTS nothreads_static)

set(BOOST_ROOT "thirdparty/boost")
set(Boost_DEBUG OFF)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
if(Boost_FOUND)
    message(STATUS "Boost_FOUND...")
endif()

add_subdirectory(mempool)
add_subdirectory(threadpool)
add_subdirectory(net)

set(dir output)
file(MAKE_DIRECTORY ${dir})
file(MAKE_DIRECTORY ${dir}/test)


set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(CMAKE_CACHEFILE_DIR ${dir})

add_executable(test/gtest_test test/test.cpp test/unittest/gtest_test.cpp net/unittest/TEST_POLL.cpp)
target_link_libraries(test/gtest_test gtest_main gtest)
add_test(NAME test/gtest_test COMMAND test/gtest_test)