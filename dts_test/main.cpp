#include <iostream>
#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

/**
 * @brief main() : runs all pre-defined tests from GTEST api.
 */
GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running main() from main.cpp" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return ::testing::UnitTest::GetInstance()->Run();
}

/**************************************end of file**************************************/
