include_directories(src .)
set(dir output)
file(MAKE_DIRECTORY ${dir})
file(MAKE_DIRECTORY ${dir}/test)
file(MAKE_DIRECTORY ${dir}/unittest)

add_executable(unittest/TEST_POLL
        src/default_event_handler.cpp
        src/event_loop.cpp
        unittest/TEST_POLL.cpp
        )
target_link_libraries(unittest/TEST_POLL gtest_main gtest gflags)
add_test(NAME unittest/TEST_POLL COMMAND unittest/TEST_POLL)