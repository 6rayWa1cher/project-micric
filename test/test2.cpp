
#include <gtest/gtest.h>
#include "../src/include/Source1.h"

TEST(Double_me, Simple_test2) {
	int x = 2;
	ASSERT_EQ(4, doubleMe(x));
}