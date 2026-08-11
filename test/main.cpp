#include <gtest/gtest.h>

int add(int a, int b) { return a + b; }

TEST(AdditionTests, HandlesPositiveInputs) { EXPECT_EQ(add(1, 2), 3); }
TEST(AdditionTests, HandlesNegativeInputs) { EXPECT_EQ(add(-1, -1), -2); }