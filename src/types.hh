#pragma once

#include <any>
#include <iosfwd>
#include <unordered_map>
#include <vector>

namespace composite {

struct none
{
};

inline bool operator==(none a, none b)
{
    return true;
}

inline bool operator!=(none a, none b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, none);

class composite;
using sequence = std::vector<composite>;                     // composite does not need to be a complete type
using mapping  = std::unordered_map<std::string, composite>; // composite is incomplete type, trickery needed

std::ostream& operator<<(std::ostream& o, const sequence& s);
std::ostream& operator<<(std::ostream& o, const mapping& m);

namespace implementation {
class mapping
{
public:
    // as templatate as composite::mapping does not have to be a complete type this way
    // however, access() is undefined behavior if T is anything other than composite::mapping
    template <typename T>
    constexpr explicit mapping(T&& m) noexcept
        : d_impl(std::forward<T>(m))
    {}

    const ::composite::mapping& access() const;

private:
    std::any d_impl;
};

bool operator==(const mapping& a, const mapping& b) noexcept;

} // namespace implementation

} // namespace composite
