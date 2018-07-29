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

/**
 * @brief Construct a new TEST object
 * 
 */
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

/**
 * @brief Construct a new TEST object
 * 
 */
TEST(UtilityTests, destroy) {
    int * p = new int(10);
    dts::destroy(p);
    EXPECT_EQ(p, nullptr);
}

/**
 * @brief Construct a new TEST object
 * 
 */
TEST(UtilityTests, uni_access) {
    std::vector<uint8_t> test_vec = {5, 3, 2, 1,};
    auto access = dts::uni_access(test_vec, 3);
    EXPECT_EQ(access, 1);
}

/************************************end of file************************************/
