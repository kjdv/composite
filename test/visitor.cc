#include "visitor.hh"
#include "sample.hh"
#include "access.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace composite {
namespace {

using namespace std;
using testing::ElementsAre;

struct scalar_collector : public visitor
{
    sequence items;

    void visit(deduce<void>::type v) override
    {
        items.emplace_back(v);
    }

    void visit(deduce<bool>::type v) override
    {
        items.emplace_back(v);
    }

    void visit(deduce<int>::type v) override
    {
        items.emplace_back(v);
    }

    void visit(deduce<double>::type v) override
    {
        items.emplace_back(v);
    }

    void visit(string_view v) override
    {
        items.emplace_back(v);
    }
};

TEST(visitor, flat)
{
    scalar_collector c;
    apply(access(sample, "scalars"), c);

    EXPECT_EQ(access(sample, "scalars").as<sequence>(), c.items);
}

TEST(visitor, flat_map)
{
    scalar_collector c;
    auto m = access(sample, "mappings", "1d");

    apply(m, c);

    EXPECT_EQ(m.as<mapping>().find("foo")->second, c.items[0]);
}

}
}
