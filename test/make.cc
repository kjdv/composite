#include "make.hh"
#include <gtest/gtest.h>

namespace composite {
namespace {

TEST(make, scalar)
{
    auto c = make_scalar(3.14);

    EXPECT_EQ(3.14, c.as<double>());
}

TEST(make, sequence)
{
    auto c = make_sequence(true, none{}, 2.72, "foo");

    auto s = c.as<sequence>();
    ASSERT_EQ(4, s.size());
    EXPECT_EQ(true, s[0].as<bool>());
    EXPECT_EQ(none{}, s[1].as<none>());
    EXPECT_EQ(2.72, s[2].as<double>());
    EXPECT_EQ("foo", s[3].as<std::string>());
}

TEST(make, empty_sequence)
{
    auto c = make_sequence();

    auto s = c.as<sequence>();
    EXPECT_TRUE(s.empty());
}

TEST(make, nested_sequence)
{
    auto c = make_sequence(
                make_sequence(1, 2),
                make_sequence(3, 4));

    auto top = c.as<sequence>();
    ASSERT_EQ(2, top.size());

    EXPECT_EQ(make_sequence(1, 2), top[0]);
    EXPECT_EQ(make_sequence(3, 4), top[1]);
}

}
}
