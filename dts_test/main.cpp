#include <iostream>
#include <algorithm>
#include <vector>

#include "../../dts/utilities.h"


// if there is a type error, and __cont is not a container of bar structs, constraint
// will throw legible error.
struct bar {
    bar() = default;
    int value = 5;
};

template <class _Container>
void
foo_bar(_Container& __cont) {
    using _Tp = typename _Container::value_type;
    dts::is_type<_Tp, bar>();

    std::for_each(__cont.begin(), __cont.end(), [&](_Tp& val)->void{
        std::cout << val.value << std::endl;
    });
}


// defined in test.cpp
extern int test();

int main() {
    std::vector<bar> test_vec(5);
    foo_bar(test_vec);

    return test();
}
