#include "types.hh"
#include "composite.hh"
#include <cassert>

#include <iostream>

namespace composite {

std::ostream &operator<<(std::ostream &o, none)
{
    return o << "<none>";
}

namespace implementation {

const ::composite::mapping &implementation::mapping::access() const
{
    auto p = std::any_cast<::composite::mapping>(&d_impl);
    assert(p != nullptr && "implementation::mapping not correctly constructed");
    return *p;
}

bool operator==(const mapping &a, const mapping &b) noexcept
{
    accessor<mapping> acc;
    return acc(a) == acc(b);
}

std::ostream &operator<<(std::ostream &o, const mapping &m)
{
    o << '{';
    const auto &impl = m.access();
    for(auto&& kv : impl)
        o << kv.first << ": " << kv.second << ", ";

    o << '}';
    return o;
}

}

std::ostream &operator<<(std::ostream &o, const sequence &s)
{
    o << '[';
    for(auto&& c : s)
        o << c << ", ";

    o << ']';
    return o;
}

}
