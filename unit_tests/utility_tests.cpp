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

    // Dynamic (stack) array test
    int array[50] = {0};
    result = dts::array_size(array);
}

TEST(UtilityTests, to_idx) {
    EXPECT_EQ(false, true);
}


/************************************end of file************************************/
