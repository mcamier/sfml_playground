
#include "gtest/gtest.h"
#include "../inc/TE/hash.hpp"

#include <string>

using namespace std;

int Factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}

void trim(string& str) {
    while(str[0] == '\n') {
        str.erase(str.begin());
    }
}
TEST(StringTrim, LeftTrim) {
    string input = "  putain";
    string expectedResult = "putain";

    trim(input);

    EXPECT_STREQ(input.c_str(), expectedResult.c_str());
}

TEST(hash, must_be_equal) {
    std::string str = "12345";
    unsigned int hash = makeHash("12345");
    unsigned int hash2 = makeHash(str);

    EXPECT_EQ(hash, hash2);
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?