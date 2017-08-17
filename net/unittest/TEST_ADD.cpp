//
// Created by Li,Datong on 8/3/17.
//

#include "gtest/gtest.h"
#include "test/test.h"

#include "t.h"

TEST(test, add)
{
    EXPECT_EQ(1, add(2,-1));
    EXPECT_EQ(5, add(2,3));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}