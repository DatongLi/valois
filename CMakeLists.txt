cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

link_libraries(pthread)

if(POLICY CMP0037)
    cmake_policy(SET CMP0037 OLD)
endif()

#add_subdirectory(thirdparty)
add_subdirectory( thirdparty/googlemock )
add_subdirectory( thirdparty/gflags )
add_subdirectory( thirdparty/glog )

include_directories(${GFLAGS_INCLUDE_DIR})
link_libraries(gflags)
link_libraries(glog)

#include_directories(thirdparty/protobuf/include)
#link_libraries(thirdparty/protobuf/lib)

#set(BOOST_ROOT "thirdparty/boost")
#set(Boost_DEBUG OFF)
#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#if(Boost_FOUND)
#    message(STATUS "Boost_FOUND...")
#endif()

include_directories(.)

#add_subdirectory(mempool)
#add_subdirectory(threadpool)
#add_subdirectory(net)

include_directories(thirdparty/libev/include)
#link_directories(thirdparty/libev/lib)
FIND_LIBRARY(EV_LIB ev thirdparty/libev/lib NO_DEFAULT_EV_PATH)
add_subdirectory(net_ev)

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
