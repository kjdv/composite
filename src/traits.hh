#pragma once

#include "types.hh"

namespace composite {

template <typename T>
struct accessor
{
    using type = T;
    const type &operator()(const T &v)
    {
        return v;
    }
};

template <>
struct accessor<implementation::mapping>
{
    using type = mapping;
    const mapping &operator()(const implementation::mapping &v)
    {
        return v.access();
    }
};

}
