#include "gtest/gtest.h"
#include "../include/tortuga/hash.hpp"
#include "../include/tortuga/core.hpp"

#include <string>

using namespace std;
using namespace ta::core;

TEST(hash, hashFromCharsOrStringShouldBeEqual) {
    string foobar = "foobar";
    const char* foobar2 = "foobar";
    unsigned int hash = makeHash(foobar);
    unsigned int otherHash = makeHash(foobar2);

    EXPECT_EQ(hash, otherHash);
}

TEST(hash, hashFromDifferentStringsShouldNotBeEqual) {
    string foobar = "foobar";
    string barfoo = "barfoo";

    unsigned int hash = makeHash(foobar);
    unsigned int otherHash = makeHash(barfoo);

    EXPECT_NE(hash, otherHash);
}
