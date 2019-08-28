#include <composite.hh>
#include <functional>
#include <iomanip>

namespace composite {

using namespace std;

bool operator==(const composite& a, const composite& b) noexcept
{
    return a.visit([&b](auto&& v) {
        using T = decay_t<decltype(v)>;

        return b.is<T>() && v == b.as<T>();
    });
}

ostream& operator<<(ostream& o, const composite& c) noexcept
{
    c.visit([&o](auto&& v) {
        o << boolalpha << v;
    });
    return o;
}

} // namespace composite
