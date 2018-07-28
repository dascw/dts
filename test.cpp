#include <iostream>
#include <forward_list>
#include <map>
#include <vector>

#include "enumerate.h"
//#include "basic.h"

int test() {
    // test routines
    std::vector<uint8_t> obj_test(5, 'A');

    // lvalue enumeration
    for (auto& a : dts::enumerate(obj_test)) {
        std::cout << a.index << ", " << a.value << std::endl;
    }

    // rvalue enumeration
    for (auto& a : dts::enumerate(std::vector<uint8_t>(5, 'B'))) {
        std::cout << a.index << ", " << a.value << std::endl;
    }

    // reduced in range loop
    std::vector<uint8_t> obj_red(10, 'C');
    for (auto& a : dts::enumerate(obj_red, (obj_red.begin() + 2), (obj_red.end() - 3))) {
        std::cout << a.index << ", " << a.value << std::endl;
    }

    // list test
    std::forward_list<uint8_t> temp_list;
    temp_list.push_front('e');
    temp_list.push_front('d');

    for (auto& a : dts::enumerate(temp_list, temp_list.begin(), temp_list.end())) {
        std::cout << a.index << ", " << a.value << std::endl;
        a.value.get() = 'f'; // to set the value of the enumeration, .get must be used.
    }

    for (auto& a : dts::enumerate(temp_list, temp_list.begin(), temp_list.end())) {
        std::cout << a.index << ", " << a.value << std::endl;
    }

    // test on a map
    std::map<int, int> test_map;
    test_map[5] = 6;
    test_map[6] = 5;

    // @note for map containers, accessing the key/value must be done using .get() method of reference_wrapper.
    for (auto& a : dts::enumerate(test_map)) {
        std::cout << a.index << ", " << a.value.get().second << std::endl;
    }

    // @note add unit test to test modification of value through reference during iteration.

    return 0;
}
