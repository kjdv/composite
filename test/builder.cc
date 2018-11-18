#include "builder.hh"
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

}
}
