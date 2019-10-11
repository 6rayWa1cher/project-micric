//
// Created by Konstantin Grigoriev on 11/10/2019.
//

#include <gtest/gtest.h>
#include "../src/coolnumber.h"

TEST(Simple_test, Simple_test) {
    ASSERT_EQ(3, 3);
    ASSERT_EQ(43, getCoolNumber());
}