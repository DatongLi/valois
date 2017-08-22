include_directories(src)
set(dir output)
file(MAKE_DIRECTORY ${dir})
file(MAKE_DIRECTORY ${dir}/test)
file(MAKE_DIRECTORY ${dir}/unittest)
add_executable(unittest/TEST_ADD src/t.cpp unittest/TEST_ADD.cpp)
target_link_libraries(unittest/TEST_ADD gtest_main gtest)
add_test(NAME unittest/poller_test COMMAND unittest/poller_test)

#target_link_libraries(test/TestMempool gflags)

#add_executable(output/unittest/poller_test src/poller.cpp unittest/poller_test.cpp)
#target_link_libraries(output/unittest/poller_test gtest_main gtest)
#add_test(NAME output/unittest/poller_test COMMAND output/unittest/poller_test)