#pragma once

#include "composite.hh"

namespace composite {

// utilities to make constructing composities less typing

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

namespace implementation
{

constexpr inline void make_sequence(sequence &s)
{}

template <typename Head, typename... Tail>
constexpr void make_sequence(sequence &s, Head&& head, Tail&&... tail)
{
    s.emplace_back(std::forward<Head>(head));
    make_sequence(s, std::forward<Tail>(tail)...);
}

}

template <typename... Ts>
composite make_sequence(Ts&&... args)
{
    sequence s;
    s.reserve(sizeof...(args));

    implementation::make_sequence(s, std::forward<Ts>(args)...);

    return composite(std::move(s));
}

}
