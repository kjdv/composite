#include "composite.hh"
#include <gtest/gtest.h>

namespace composite {
namespace {

TEST(composite, default_constructs_as_none)
{
    composite c;

    EXPECT_TRUE(c.is<none>());
    EXPECT_TRUE(c.is<void>());
    EXPECT_TRUE(c.is<const none &>());

    EXPECT_EQ(none{}, c.as<none>());
    EXPECT_EQ(none{}, c.as<void>());
}

TEST(composite, construct_int)
{
    /*
    composite c;

    EXPECT_FALSE(c.is<none>());
    EXPECT_TRUE(c.is<int>());
    EXPECT_TRUE(c.is<int64_t>());

    EXPECT_EQ(1, c.as<int>());*/
}

}
}
