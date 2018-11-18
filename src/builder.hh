#pragma once

#include "composite.hh"
#include <stack>
#include <variant>

namespace composite {

class builder
{
public:
    template <typename T>
    builder &with(T &&value);

    template <typename T>
    builder &with(std::string_view key, T &&value);

    builder &push_sequence();
    builder &push_sequence(std::string_view key);

    builder &push_mapping();
    builder &push_mapping(std::string_view key);

    builder &pop();

    composite build();
private:
    bool is_sequence() const;

    bool is_mapping() const;

    bool is_top() const;

    sequence &as_seq();

    mapping &as_map();

    struct item
    {
        std::variant</* scalar */ composite, sequence, mapping> value;
        std::optional<std::string> key;
    };
    std::stack<item> d_stack;
};

template <typename T>
builder &builder::with(T && value)
{
    if(is_top())
        d_stack.emplace(item{{composite(std::forward<T>(value))}});
    else
        as_seq().emplace_back(std::forward<T>(value));
    return *this;
}

template <typename T>
builder &builder::with(std::string_view key, T&& value)
{
    as_map().emplace(key, std::forward<T>(value));
    return *this;
}

}
