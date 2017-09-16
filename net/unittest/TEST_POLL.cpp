//
// Created by lidatong on 9/6/17.
//

#include "gtest/gtest.h"
#include "net/src/event_loop.h"
#ifdef HAVE_EPOLL
    #include "va_epoll.h"
    #else
        #ifdef HAVE_KQUEUE
            #include "va_kqueue.h"
        #else
            #include "va_select.h"
        #endif
#endif
TEST(test, EventResize)
{
    valois::net::PollBase *pb = new valois::net::Poll();
    EXPECT_EQ(0, pb->EventResize(NULL, 0));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}