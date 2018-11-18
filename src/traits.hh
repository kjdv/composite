#pragma once

#include "types.hh"

namespace composite {

template <typename T>
struct accessor
{
    using type = T;
    constexpr const type& operator()(const T& v) const
    {
        return v;
    }
};

template <>
struct accessor<implementation::mapping>
{
    using type = mapping;
    const mapping& operator()(const implementation::mapping& v) const
    {
        return v.access();
    }
};

} // namespace composite
