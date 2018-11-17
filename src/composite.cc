#include "composite.hh"
#include <functional>
#include <iomanip>

namespace composite {

using namespace std;

bool operator==(const composite &a, const composite &b) noexcept
{
    return a.d_data == b.d_data;
}

ostream &operator<<(ostream &o, const composite &c) noexcept
{
    return c.visit([&o](auto&& v) {
        using T = std::decay_t<decltype(v)>;
        accessor<T> acc;

        o << boolalpha << acc(v);
        return std::ref(o);
    });
}

size_t hash(const composite &c) noexcept
{
    std::hash<composite::variant_t> hasher{};
    return hasher(c.d_data);
}

}

