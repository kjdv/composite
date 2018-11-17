#pragma once

#include <iosfwd>
#include <vector>
#include <any>
#include <unordered_map>

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

class composite;
using sequence = std::vector<composite>; // composite does not need to be a complete type
using mapping = std::unordered_map<std::string, composite>; // composite is incomplete type, trickery needed

namespace implementation
{
    class mapping
    {
    public:
        template <typename T>
        constexpr explicit mapping(T&& m) noexcept
            : d_impl(std::forward<T>(m))
        {}

        const ::composite::mapping &access() const;
    private:
        std::any d_impl;
    };
}

}
