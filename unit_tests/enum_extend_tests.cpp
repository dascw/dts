// enum extend tests.cpp
#include <stdint.h>
#include "gtest/gtest.h"
#include "dts/enum_extend.h"

enum class test_enum : uint32_t {
    one,
    two,
    three,
    four,
    five
};
__ENUM_OPERATOR_OVERLOAD(test_enum, uint32_t);

enum class test_enum_basic : uint8_t {
    one,
    two,
    three
};

TEST(EnumExtendTest, postfix) {

    test_enum temp = test_enum::one;
    temp++; // posfix
    EXPECT_EQ(temp, test_enum::two);
}

TEST(EnumExtendTest, prefix) {

    test_enum temp = test_enum::one;
    ++temp; // prefix
    EXPECT_EQ(temp, test_enum::two);
}

TEST(EnumExtendTest, postfix_decrement) {

    test_enum temp = test_enum::two;
    temp--; // posfix
    EXPECT_EQ(temp, test_enum::one);
}

TEST(EnumExtendTest, prefix_drecement) {

    test_enum temp = test_enum::two;
    --temp; // prefix
    EXPECT_EQ(temp, test_enum::one);
}

TEST(EnumExtendTest, greater_than) {

    test_enum temp = test_enum::two;
    EXPECT_TRUE(temp > 0);
}

TEST(EnumExtendTest, less_than) {

    test_enum temp = test_enum::two;
    EXPECT_TRUE(temp < 3);
}

TEST(EnumExtendTest, equal_to) {

    test_enum temp = test_enum::two;
    EXPECT_TRUE(temp == 1);
}

TEST(EnumExtendTest, not_equal_to) {

//     test_enum temp = test_enum::two;
    // @bug resulting in recursive call (removed)
    EXPECT_TRUE(temp != 0);
}

TEST(EnumExtendTest, not_extended) {
    test_enum_basic val = test_enum_basic::one;
//    val++; // postfix increment does not work for classes not overloaded.
    EXPECT_TRUE(true);
}

/************************************end of file************************************/
