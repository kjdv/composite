#include "visitor.hh"
#include "access.hh"
#include "sample.hh"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stack>

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

class jsonify : public visitor
{
public:
    explicit jsonify()
    {
        d_str << boolalpha;
    }

    void visit(deduce<void>::type v) override
    {
        d_str << "null";
    }

    void visit(deduce<bool>::type v) override
    {
        d_str << v;
    }

    void visit(deduce<int>::type v) override
    {
        d_str << v;
    }

    void visit(deduce<double>::type v) override
    {
        d_str << v;
    }

    void visit(string_view v) override
    {
        d_str << quoted(v);
    }

    void index(std::size_t idx) override
    {
        if(idx > 0)
            d_str << ", ";
    }

    void key(string_view key) override
    {
        assert(!d_state.empty());

        if(d_state.top() == state::map_first)
        {
            d_state.pop();
            d_state.push(state::map_next);
        }
        else
            d_str << ", ";

        d_str << quoted(key) << ": ";
    }

    void start_sequence() override
    {
        d_str << '[';
        d_state.push(state::seq);
    }

    void start_mapping() override
    {
        d_str << '{';
        d_state.push(state::map_first);
    }

    void sentinel() override
    {
        assert(!d_state.empty());

        switch(d_state.top())
        {
        case state::seq:
            d_str << ']';
            break;
        case state::map_first:
        case state::map_next:
            d_str << '}';
        }
        d_state.pop();
    }

    string build()
    {
        assert(d_state.empty());
        return d_str.str();
    }

private:
    std::ostringstream d_str;

    enum class state { seq,
                       map_first,
                       map_next };
    stack<state> d_state;
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
    auto             m = access(sample, "mappings", "1d");

    apply(m, c);

    EXPECT_EQ(m.as<mapping>().find("foo")->second, c.items[0]);
}

TEST(visitor, jsonify_scalar)
{
    jsonify js;
    apply(access(sample, "scalars", 4), js);

    EXPECT_EQ("3.14", js.build());
}

TEST(visitor, jsonify_seq)
{
    jsonify js;
    apply(access(sample, "scalars"), js);

    EXPECT_EQ(R"|([null, true, false, 1, 3.14, "foo"])|", js.build());
}

TEST(visitor, jsonify_map)
{
    jsonify js;
    apply(access(sample, "mappings", "2d"), js);

    // todo: this is not deterministic
    EXPECT_EQ(R"|({"b": {"e": 2.72}, "a": {"pi": 3.14}})|", js.build());
}

} // namespace
} // namespace composite
