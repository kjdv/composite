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
        using T = decay_t<decltype(v)>;
        if constexpr (is_same<T, none>::value)
            o << v;
        else if constexpr (is_same<T, bool>::value)
            o << boolalpha << v;
        else if constexpr (is_same<T, int64_t>::value)
            o << v;
        else if constexpr (is_same<T, double>::value)
            o << v;
        else if constexpr (is_same<T, string>::value)
            o << quoted(v);
        else if constexpr (is_same<T, sequence>::value)
            o << v;
        else if constexpr (is_same<T, implementation::mapping>::value)
            o << v;

        return std::ref(o);
    });
}

}
