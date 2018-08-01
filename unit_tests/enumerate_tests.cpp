#include <iostream>
#include <forward_list>
#include <map>
#include <vector>
#include "gtest/gtest.h"

#include "dts/base_macro.h"
#include "dts/enumerate.h"

///! macro for basic testing of enumeration members.
#define ENUMERATE_TEST_BASIC(arg, ENUMERATE, idx_init) \
    int index = idx_init; \
    for (auto& a : ENUMERATE) { \
        ASSERT_EQ(index++, a.index); \
        ASSERT_EQ(a.value, arg); \
    } dts_EAT_SEMICOLON() \


TEST(EnumerateTests, lvalue_enumeration) {
    // test routines
    std::vector<uint8_t> obj_test(5, 'A');
    ENUMERATE_TEST_BASIC('A', dts::enumerate(obj_test), 0);
}

TEST(EnumerateTests, rvalue_enumeration) {
    // rvalue enumeration
    ENUMERATE_TEST_BASIC('B', dts::enumerate(std::vector<uint8_t>(5, 'B')), 0);
}

TEST(EnumerateTests, reduced_in_range) {
    // reduced in range loop
    std::vector<uint8_t> obj_red(10, 'C');
    ENUMERATE_TEST_BASIC('C', dts::enumerate(obj_red, \ 
                                            (obj_red.begin() + 2), \ 
                                            (obj_red.end() - 3)), 2);
}

TEST(EnumerateTests, list_container) {
    // list test
    std::forward_list<uint8_t> temp_list;
    std::vector<uint8_t> test_data({'e', 'e'});
    for (const auto &a : test_data)
        temp_list.push_front(a);

    int index = 0;

    for (auto& a : dts::enumerate(temp_list, temp_list.begin(), temp_list.end())) {
        ASSERT_EQ(a.value, test_data[index]);
        ASSERT_EQ(a.index, index++);
        a.value.get() = 'f'; // to set the value of the enumeration, .get must be used.
    }

    // check lvalue modification was successful.
    for (auto& a : dts::enumerate(temp_list))
        ASSERT_EQ(a.value, 'f');
}

TEST(EnumerateTests, map_container) {
    std::map<int, int> test_map;
    std::vector<uint8_t> test_keys({5, 6});
    std::vector<uint8_t> test_data = test_keys;
    std::reverse(test_data.begin(), test_data.end());

    test_map[5] = 6;
    test_map[6] = 5;
    int index = 0;

    // @note for map containers, accessing the key/value must be done using 
    // .get() method of reference_wrapper.
    for (auto& a : dts::enumerate(test_map)) {
        ASSERT_EQ(a.value.get().first, test_keys[index]);
        ASSERT_EQ(a.value.get().second, test_data[index]);
        ASSERT_EQ(a.index, index++);
    }
}

/************************************end of file************************************/
