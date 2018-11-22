#include <composite/access.hh>
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

TEST(access, nested)
{
    EXPECT_EQ("Laika", access(sample, "mappings", "seq", "spacedogs", 0).as<string>());
    EXPECT_EQ("Belka", access(sample, "mappings", "seq", "spacedogs", 1).as<string>());
    EXPECT_EQ("Strelka", access(sample, "mappings", "seq", "spacedogs", 2).as<string>());
}

TEST(access, index_on_nonsequence_throws)
{
    EXPECT_THROW(access(sample, 0), bad_access);
}

TEST(access, index_out_of_range_throws)
{
    EXPECT_THROW(access(sample, "scalars", 6), bad_access);
}

TEST(access, key_on_nonmap_throws)
{
    EXPECT_THROW(access(sample, "scalars", "double"), bad_access);
}

TEST(access, bad_key_throws)
{
    EXPECT_THROW(access(sample, "mappings", "3d"), bad_access);
}

} // namespace
} // namespace composite
