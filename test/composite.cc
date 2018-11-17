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

TEST(composite, construct_sequence)
{
    sequence s{composite(1), composite(3.14), composite("foo")};
    composite c(s);

    EXPECT_TRUE(c.is<sequence>());

    const sequence &a = c.as<sequence>();
    ASSERT_EQ(3, a.size());
    EXPECT_EQ(1, a[0].as<int>());
    EXPECT_EQ(3.14, a[1].as<double>());
    EXPECT_EQ("foo", a[2].as<std::string>());
}

TEST(composite, construct_mapping)
{
    mapping m{{"pi", composite(3.14)}};
    composite c(m);

    EXPECT_TRUE(c.is<mapping>());

    const mapping &a = c.as<mapping>();
    auto it = a.find("pi");
    ASSERT_NE(a.end(), it);
    EXPECT_EQ(3.14, it->second.as<double>());
}

TEST(composite, is_copy_constructable)
{
    static_assert(std::is_copy_constructible<composite>::value);

    composite a(3.14);
    composite b(a);

    EXPECT_EQ(3.14, b.as<double>());
    EXPECT_EQ(a.as<double>(), b.as<double>());
}

TEST(composite, is_copy_assignable)
{
    static_assert(std::is_copy_assignable<composite>::value);

    composite a(3.14);
    composite b;
    EXPECT_EQ(none{}, b.as<none>());

    b = a;
    EXPECT_EQ(3.14, b.as<double>());
    EXPECT_EQ(a.as<double>(), b.as<double>());
}

TEST(composite, is_move_constructable)
{
    static_assert(std::is_move_constructible<composite>::value);

    composite a(3.14);
    composite b(std::move(a));

    EXPECT_EQ(3.14, b.as<double>());
}

TEST(composite, is_move_assignable)
{
    static_assert(std::is_move_assignable<composite>::value);

    composite a(3.14);
    composite b;
    EXPECT_EQ(none{}, b.as<none>());

    b = std::move(a);
    EXPECT_EQ(3.14, b.as<double>());
}

TEST(composite, equality)
{
    struct{
        composite left;
        composite right;
        bool equal;
    } testcases[] = {
        {composite(), composite(), true},
        {composite(false), composite(false), true},
        {composite(1), composite(1), true},
        {composite(-3.14), composite(-3.14), true},
        {composite("foo"), composite("foo"), true},

        {composite(true), composite(false), false},
        {composite(-1), composite(1), false},
        {composite(3.14), composite(3.15), false},
        {composite("foo"), composite("bar"), false},

        {composite(none{}), composite(1), false},
        {composite(2), composite(2.0), false},
    };

    for (auto&& tc : testcases)
    {
        EXPECT_EQ(tc.equal, tc.left == tc.right);
        EXPECT_NE(tc.equal, tc.left != tc.right);
    }
}


}
}
