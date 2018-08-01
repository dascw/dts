#include <iostream>
#include <forward_list>
#include <map>
#include <vector>
#include <memory>
#include <tuple>
#include "gtest/gtest.h"

#include "dts/utilities.h"

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
        three,
        four
    };
    EXPECT_EQ(0, dts::to_idx(test_enum::one));
    EXPECT_EQ(1, dts::to_idx(test_enum::two));
    EXPECT_EQ(3, dts::to_idx(test_enum::four));

    std::vector<test_enum> test_vec({test_enum::one, test_enum::two, test_enum::three, test_enum::four});

    for (auto idx = 0; idx < test_vec.size(); ++idx) {
        EXPECT_EQ(dts::to_idx(test_vec[idx]), idx);
    }
}

TEST(UtilityTests, destroy) {
    int * p = new int(10);
    dts::destroy(p);
    EXPECT_EQ(p, nullptr);
}

TEST(UtilityTests, uni_access) {
    std::vector<uint8_t> test_vec = {5, 3, 2, 1,};
    auto& access = dts::uni_access(test_vec, 3);
    EXPECT_EQ(access, 1);
    access = 5;
    EXPECT_EQ(5, test_vec[3]);
}

#if __cplusplus > dts_CPP_11
TEST(UtilityTests, utype_tuple) {
    enum class test_enum : uint8_t {
        name,
        value_one,
        value_two
    };

    auto test_tuple = std::make_tuple("Test", 1, 5.5);
    auto val = std::get<dts::utype(test_enum::name)>(test_tuple);

    EXPECT_EQ(val, "Test");
}
#endif // C11
/************************************end of file************************************/
