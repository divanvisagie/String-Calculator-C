#include <gtest/gtest.h>

// Stub function that you might want to test
int add(int a, int b) {
    return a + b;
}

// A test case
TEST(AdditionTests, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 1), 2);
}

TEST(AdditionTests, HandlesZeroInput) {
    EXPECT_EQ(add(0, 0), 0);
}

TEST(AdditionTests, HandlesMixedInput) {
    EXPECT_EQ(add(-1, 1), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
