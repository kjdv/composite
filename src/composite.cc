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
        o << boolalpha << v;
        return std::ref(o);
    });
}

}
