#include <gtest/gtest.h>
#include <ProcessRunner.hpp>

int add(int a, int b) { return a + b; }

TEST(ProcessRunnerTests, echo) {
    EXPECT_EQ(ProcessRunner::exec("echo hi"), "hi\n"); 
}