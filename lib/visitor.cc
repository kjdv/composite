#include <visitor.hh>
#include <cassert>

namespace composite {

namespace {

struct helper
{
    visitor& base;

    template <typename T>
    void operator()(T&& item)
    {
        base.visit(std::forward<T>(item));
    }

    void operator()(const sequence& s)
    {
        base.start_sequence();

        for(size_t i = 0; i < s.size(); ++i)
        {
            base.index(i);
            apply(s[i], base);
        }

        base.end_sequence();
        base.sentinel(); // todo: remove deprecated call
    }

    void operator()(const mapping& m)
    {
        base.start_mapping();

        for(auto&& kv : m)
        {
            base.key(kv.first);
            apply(kv.second, base);
        }

        base.end_mapping();
        base.sentinel(); // todo: remove deprecated call
    }
};

} // namespace

void visitor::index(std::size_t)
{}

void visitor::key(std::string_view)
{}

void visitor::start_sequence()
{}

void visitor::start_mapping()
{}

void visitor::end_sequence()
{
}

void visitor::end_mapping()
{
}

void visitor::sentinel()
{}

void apply(const composite& c, visitor& v)
{
    c.visit(helper{v});
}

} // namespace composite
