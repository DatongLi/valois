//
// Created by lidatong on 9/6/17.
//

#include "gtest/gtest.h"
#include "net/src/event_loop.h"

TEST(test, EventResize)
{
    PollBase *pb = new Poll();
    EXPECT_EQ(1, pb->EventResize(NULL,0));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}