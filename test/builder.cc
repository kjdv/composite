#include <composite/builder.hh>
#include <composite/access.hh>
#include "sample.hh"
#include <gtest/gtest.h>

// clang-format off

namespace composite {
namespace {

TEST(builder, scalar)
{
    EXPECT_EQ(make(none{}), builder().with(none{}).build());
    EXPECT_EQ(make(true), builder().with(true).build());
    EXPECT_EQ(make(1), builder().with(1).build());
    EXPECT_EQ(make(1.41), builder().with(1.41).build());
    EXPECT_EQ(make("foobar"), builder().with("foobar").build());
}

TEST(builder, sequence)
{
    auto c = builder()
        .push_sequence()
            .with(1)
            .with(2)
            .with(3)
        .pop()
        .build();

    EXPECT_EQ(make_seq(1, 2, 3), c);
}

TEST(builder, mapping)
{
    auto c = builder()
        .push_mapping()
            .with("foo", "bar")
            .with("pi", 3.14)
        .pop()
        .build();

    EXPECT_EQ(make_map("foo", "bar", "pi", 3.14), c);
}

TEST(builder, complex)
{
    auto c = builder()
        .push_mapping()
            .push_sequence("scalars")
                .with(none{})
                .with(true)
                .with(false)
                .with(1)
                .with(3.14)
                .with("foo")
            .pop()
            .push_mapping("sequences")
                .push_sequence("1d")
                    .with(1)
                    .with(2)
                    .with(3)
                .pop()
                .push_sequence("2d")
                    .push_sequence()
                        .with(1)
                        .with(2)
                    .pop()
                    .push_sequence()
                        .with(3)
                        .with(4)
                    .pop()
                    .push_sequence()
                        .with(5)
                        .with(6)
                    .pop()
                .pop()
                .push_sequence("map")
                    .push_mapping()
                        .with("foo", "bar")
                    .pop()
                    .push_mapping()
                        .with("bar", "foo")
                    .pop()
                .pop()
            .pop()
            .push_mapping("mappings")
                .push_mapping("1d")
                    .with("foo", "bar")
                .pop()
                .push_mapping("2d")
                    .push_mapping("a")
                        .with("pi", 3.14)
                    .pop()
                    .push_mapping("b")
                        .with("e", 2.72)
                    .pop()
                .pop()
                .push_mapping("seq")
                    .push_sequence("spacedogs")
                        .with("Laika")
                        .with("Belka")
                        .with("Strelka")
                    .pop()
                .pop()
            .pop()
        .pop()
        .build();

    // allow progressive failure discovery, test subitems first
    EXPECT_EQ(access(sample, "scalars"), access(c, "scalars"));

    EXPECT_EQ(access(sample, "sequences", "1d"), access(c, "sequences", "1d"));
    EXPECT_EQ(access(sample, "sequences", "2d"), access(c, "sequences", "2d"));
    EXPECT_EQ(access(sample, "sequences", "map"), access(c, "sequences", "map"));
    EXPECT_EQ(access(sample, "sequences"), access(c, "sequences"));

    EXPECT_EQ(access(sample, "mappings"), access(c, "mappings"));

    // finally, show full equivalence:
    EXPECT_EQ(sample, c);
}

}
}
