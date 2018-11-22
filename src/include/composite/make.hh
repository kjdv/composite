#pragma once

#include "composite.hh"
#include <string_view>

namespace composite {

// utilities to make constructing composities less typing
// check builder if you need something more dynamic

template <typename T>
composite make(T&& v)
{
    return composite(std::forward<T>(v));
}

template <typename T>
composite make_scalar(T&& v)
{
    return make(std::forward<T>(v));
}

namespace implementation {

constexpr inline void make_sequence(sequence& s)
{}

template <typename Head, typename... Tail>
constexpr void make_sequence(sequence& s, Head&& head, Tail&&... tail)
{
    s.emplace_back(std::forward<Head>(head));
    implementation::make_sequence(s, std::forward<Tail>(tail)...);
}

constexpr inline void make_mapping(::composite::mapping& m)
{}

template <typename Head, typename... Tail>
constexpr void make_mapping(::composite::mapping& m, std::string_view key, Head&& value, Tail&&... tail)
{
    m.emplace(key, value);
    implementation::make_mapping(m, std::forward<Tail>(tail)...);
}

} // namespace implementation

template <typename... Ts>
composite make_sequence(Ts&&... args)
{
    sequence s;
    s.reserve(sizeof...(args));

    implementation::make_sequence(s, std::forward<Ts>(args)...);

    return composite(std::move(s));
}

template <typename... Ts>
composite make_seq(Ts&&... args) // shorthand
{
    return make_sequence(std::forward<Ts>(args)...);
}

template <typename... Ts>
composite make_mapping(Ts&&... args)
{
    static_assert((sizeof...(args) & 1) == 0, "arguments are key-value pairs, their number must be even");

    mapping m;
    m.reserve(sizeof...(args));

    implementation::make_mapping(m, std::forward<Ts>(args)...);

    return composite(std::move(m));
}

template <typename... Ts>
composite make_map(Ts&&... args)
{
    return make_mapping(std::forward<Ts>(args)...);
}

} // namespace composite
