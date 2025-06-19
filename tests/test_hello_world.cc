#include <gtest/gtest.h>

TEST(HelloWorldTest, Basic) {
    ASSERT_STREQ("Hello World", "Hello World");
}
