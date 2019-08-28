#include <make.hh>
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
    auto c = make_seq(
        make_seq(1, 2),
        make_seq(3, 4));

    auto top = c.as<sequence>();
    ASSERT_EQ(2, top.size());

    EXPECT_EQ(make_sequence(1, 2), top[0]);
    EXPECT_EQ(make_sequence(3, 4), top[1]);
}

TEST(make, mapping)
{
    auto c = make_mapping("pi", 3.14, "e", 2.72, "void", none{});

    auto m = c.as<mapping>();

    auto get = [&m](std::string key) {
        auto it = m.find(key);
        assert(m.end() != it);
        return it->second;
    };

    EXPECT_EQ(make(3.14), get("pi"));
    EXPECT_EQ(make(2.72), get("e"));
    EXPECT_EQ(make(none{}), get("void"));
}

TEST(make, empty_mapping)
{
    auto c = make_mapping();
    auto m = c.as<mapping>();

    EXPECT_TRUE(m.empty());
}

TEST(make, nested_mapping)
{
    auto c = make_map(
        "a", make_map("pi", 3.14), "b", make_map("e", 2.72));
    auto m = c.as<mapping>();

    EXPECT_EQ(make_map("pi", 3.14), m.find("a")->second);
    EXPECT_EQ(make_map("e", 2.72), m.find("b")->second);
}

TEST(make, seq_in_map)
{
    auto c = make_map(
        "seq", make_seq(1, 2, 3));

    EXPECT_EQ(make_seq(1, 2, 3), c.as<mapping>().find("seq")->second);
}

TEST(make, map_in_seq)
{
    auto c = make_seq(
        make_map(
            "a", "foo"),
        make_map(
            "b", "bar"));

    EXPECT_EQ(make_map("a", "foo"), c.as<sequence>()[0]);
    EXPECT_EQ(make_map("b", "bar"), c.as<sequence>()[1]);
}

} // namespace
} // namespace composite
