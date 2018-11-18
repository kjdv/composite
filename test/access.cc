#include "access.hh"
#include "sample.hh"
#include <gtest/gtest.h>

namespace composite {
namespace {

using namespace std;

TEST(access, scalars)
{
    EXPECT_EQ(none{}, access(sample, "scalars", 0).as<none>());
    EXPECT_EQ(true, access(sample, "scalars", 1).as<bool>());
    EXPECT_EQ(false, access(sample, "scalars", 2).as<bool>());
    EXPECT_EQ(1, access(sample, "scalars", 3).as<int>());
    EXPECT_EQ(3.14, access(sample, "scalars", 4).as<double>());
    EXPECT_EQ("foo", access(sample, "scalars", 5).as<string>());

}

}
}
