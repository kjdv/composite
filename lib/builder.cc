#include <builder.hh>
#include <cassert>

namespace composite {

using namespace std;

builder& builder::push_sequence()
{
    d_stack.emplace(item{sequence{}});
    return *this;
}

builder& builder::push_sequence(string_view key)
{
    d_stack.emplace(item{sequence{}, string{key}});
    return *this;
}

builder& builder::push_mapping()
{
    d_stack.emplace(item{mapping{}});
    return *this;
}

builder& builder::push_mapping(string_view key)
{
    d_stack.emplace(item{mapping{}, string{key}});
    return *this;
}

builder& builder::pop()
{
    assert(!d_stack.empty());

    item i = move(d_stack.top());
    d_stack.pop();

    if(is_sequence())
    {
        assert(!i.key.has_value());

        visit([this](auto&& v) {
            using T = decay_t<decltype(v)>;
            as_seq().emplace_back(std::forward<T>(v));
        },
              i.value);
    }
    else if(is_mapping())
    {
        assert(i.key.has_value());

        auto key = *i.key;
        visit([this, key](auto&& v) {
            using T = decay_t<decltype(v)>;
            as_map().emplace(key, std::forward<T>(v));
        },
              i.value);
    }
    else
    {
        assert(d_stack.empty());
        auto c = visit([](auto&& v) {
            using T = decay_t<decltype(v)>;
            return composite(std::forward<T>(v));
        },
                       i.value);

        d_stack.emplace(item{c});
    }

    return *this;
}

composite builder::build()
{
    assert(d_stack.size() == 1);
    auto c = move(d_stack.top());
    d_stack.pop();

    return visit([](auto&& v) {
        using T = decay_t<decltype(v)>;
        return composite(std::forward<T>(v));
    },
                 c.value);
}

bool builder::is_sequence() const
{
    return !d_stack.empty() && holds_alternative<sequence>(d_stack.top().value);
}

bool builder::is_mapping() const
{
    return !d_stack.empty() && holds_alternative<mapping>(d_stack.top().value);
}

bool builder::is_top() const
{
    return d_stack.empty();
}

sequence& builder::as_seq()
{
    assert(is_sequence());
    return get<sequence>(d_stack.top().value);
}

mapping& builder::as_map()
{
    assert(is_mapping());
    return get<mapping>(d_stack.top().value);
}

} // namespace composite
