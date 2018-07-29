#include <iostream>
#include <forward_list>
#include <map>
#include <vector>
#include <memory>
#include "gtest/gtest.h"

#include "utilities.h"

/**
 * @brief Construct a new TEST object
 */
TEST(UtilityTests, array_size) {
    // Const array test
    const uint8_t test_array[15] = {0};    
    auto result = dts::array_size(test_array);
    EXPECT_EQ(result, 15);

    // stack allocated array test
    int array[50] = {0};
    result = dts::array_size(array);
    EXPECT_EQ(result, 50);
}

TEST(UtilityTests, to_idx) {
    enum class test_enum : uint8_t {
        one,
        two,
        four = 4
    };

    EXPECT_EQ(0, dts::to_idx(test_enum::one));
    EXPECT_EQ(1, dts::to_idx(test_enum::two));
    EXPECT_EQ(4, dts::to_idx(test_enum::four));
}


/************************************end of file************************************/
