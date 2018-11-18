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
    c.visit([&o](auto&& v) {
        o << boolalpha << v;
    });
    return o;
}

size_t hash(const composite &c) noexcept
{
    std::hash<composite::variant_t> hasher{};
    return hasher(c.d_data);
}

}

