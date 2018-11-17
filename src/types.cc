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

namespace std {
namespace {

// borrowed from boost
template <typename T>
void hash_combine(std::size_t& seed, const T& v) noexcept
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

}

hash<composite::none>::result_type hash<composite::none>::operator()(argument_type) const noexcept
{
    return 0;
}

hash<composite::sequence>::result_type hash<composite::sequence>::operator()(const argument_type &s) const noexcept
{
    result_type r{0};

    for(auto&& v : s)
        hash_combine(r, v);

    return r;
}

hash<composite::implementation::mapping>::result_type hash<composite::implementation::mapping>::operator()(const argument_type &m) const noexcept
{
    result_type r{0};

    auto& impl = m.access();
    for(auto&& kv : impl)
    {
        hash_combine(r, kv.first);
        hash_combine(r, kv.second);
    }

    return r;
}

}
