#include "gtest/gtest.h"
#include "class1.h"

TEST(SimpleTest, SimpleTest) {
  Class1 c;
  c.Method1();
  ASSERT_TRUE(true);
}
