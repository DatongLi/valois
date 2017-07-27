cmake_minimum_required(VERSION 2.8)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in thirdparty/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#SET(CMAKE_C_COMPILER "/usr/bin/g++")
SET(CMAKE_BINARY_DIR .)
ADD_DEFINITIONS(-g -O0)
add_compile_options(-std=c++11)

include_directories(mempool/src threadpool/src net/src .)

add_executable(mempool/output/TestMempool mempool/example/TestMempool.cpp)

link_libraries(pthread)
add_executable(threadpool/output/TestThreadpool threadpool/example/TestThreadpool.cpp)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/thirdparty/googletest-src
                 ${CMAKE_BINARY_DIR}/thirdparty/googletest-build)
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(output/gtest_test test/test.cpp test/unittest/gtest_test.cpp)
target_link_libraries(output/gtest_test gtest_main gtest)
add_test(NAME output/gtest_test COMMAND output/gtest_test)