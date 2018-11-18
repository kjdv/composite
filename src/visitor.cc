#include "visitor.hh"
#include <cassert>

namespace composite {

namespace {

struct helper
{
    visitor &base;

    template <typename T>
    void operator()(T&& item)
    {
        base.visit(std::forward<T>(item));
    }

    void operator()(const sequence &s)
    {
        base.start_sequence();

        for(auto&& item : s)
            apply(item, base);

        base.sentinel();
    }

    void operator()(const mapping &m)
    {
        base.start_mapping();

        for(auto&& kv : m)
            apply(kv.second, base);

        base.sentinel();
    }
};

}

void visitor::index(std::size_t)
{}

void visitor::key(std::string_view)
{}

void visitor::start_sequence()
{}

void visitor::start_mapping()
{}

void visitor::sentinel()
{}


void apply(const composite &c, visitor &v)
{
    c.visit(helper{v});
}

}
