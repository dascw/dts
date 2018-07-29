#include <iostream>
#include <forward_list>
#include <map>
#include <vector>
#include "gtest/gtest.h"

#include "utilities.h"

/**
 * @brief Construct a new TEST object
 */
TEST(UtilityTests, array_size) {
    const uint8_t test_array[15] = {0};
    
    auto result = dts::array_size(test_array);
    EXPECT_EQ(result, 15);
}

TEST(UtilityTests, to_idx) {
    EXPECT_EQ(false, true);
}


/************************************end of file************************************/