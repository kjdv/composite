#include "types.hh"
#include "composite.hh"
#include <cassert>
#include <algorithm>
#include <iostream>

namespace composite {

using namespace std;

ostream &operator<<(ostream &o, none)
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

}

ostream &operator<<(ostream &o, const mapping &m)
{
    o << '{';

    bool first = true;
    for(auto&& kv : m)
    {
        if(!first)
            o << ", ";
        o << kv.first << ": " << kv.second;
        first = false;
    }

    o << '}';
    return o;
}

ostream &operator<<(ostream &o, const sequence &s)
{
    o << '[';

    bool first = true;
    for(auto&& c : s)
    {
        if(!first)
            o << ", ";
        o << c;
        first = false;
    }

    o << ']';
    return o;
}

}
