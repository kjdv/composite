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

TEST(composite, construct_bool)
{
    composite t(true);
    composite f(false);

    EXPECT_TRUE(t.is<bool>());
    EXPECT_FALSE(f.is<int>());

    EXPECT_TRUE(t.as<bool>());
    EXPECT_FALSE(f.as<bool>());
}

TEST(composite, construct_int)
{
    composite c(1);

    EXPECT_FALSE(c.is<none>());
    EXPECT_TRUE(c.is<int>());
    EXPECT_TRUE(c.is<int64_t>());

    EXPECT_EQ(1, c.as<int>());
}

TEST(composite, construct_float)
{
    double p = 3.1415;
    composite c(p);

    EXPECT_FALSE(c.is<int>());
    EXPECT_TRUE(c.is<float>());
    EXPECT_TRUE(c.is<double>());

    EXPECT_EQ(p, c.as<double>());
}

TEST(composite, construct_string)
{
    composite c("foo");

    EXPECT_TRUE(c.is<std::string>());
    EXPECT_EQ("foo", c.as<std::string>());
}

}
}
