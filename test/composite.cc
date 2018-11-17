#include "composite.hh"
#include <gtest/gtest.h>

namespace composite {
namespace {

TEST(composite, default_constructs_as_none)
{
    composite c;

    EXPECT_TRUE(c.is<none>());
    EXPECT_EQ(none{}, c.as<none>());
}

}
}
