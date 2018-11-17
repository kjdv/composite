#pragma once

#include <iosfwd>
#include <vector>
#include <unordered_map>
#include <any>

namespace composite {

struct none{};

inline bool operator==(none a, none b)
{
    return true;
}

inline bool operator!=(none a, none b)
{
    return !(a == b);
}

std::ostream &operator<<(std::ostream &o, none);

class sequence
{};

class mapping
{};


}
