#pragma once

#include <variant>
#include <string>
#include "types.hh"
#include "deduce.hh"
#include "traits.hh"

namespace composite {

class composite {
public:
    constexpr explicit composite() noexcept
        : d_data{none{}}
    {}

    template <typename T, typename = typename decay_deduce<T>::type>
    constexpr explicit composite(T&& value) noexcept
        : d_data(std::in_place_type<typename decay_deduce<T>::type>, std::forward<T>(value))
    {}


    template <typename T>
    constexpr bool is() const noexcept;

    template <typename T>
    constexpr const typename accessor<typename decay_deduce<T>::type>::type &as() const;

private:
    friend bool operator==(const composite &, const composite &) noexcept;

    std::variant<
        deduce<none>::type,
        deduce<bool>::type,
        deduce<int>::type,
        deduce<double>::type,
        deduce<std::string>::type,
        deduce<sequence>::type,
        implementation::mapping // small kludge, composite::mapping is an incomplete type at this point
    > d_data;
};

bool operator==(const composite &a, const composite &b) noexcept;

inline bool operator!=(const composite &a, const composite &b) noexcept
{
    return !(a == b);
}

template <typename T>
constexpr bool composite::is() const noexcept
{
    return std::holds_alternative<typename decay_deduce<T>::type>(d_data);
}

template <typename T>
constexpr const typename accessor<typename decay_deduce<T>::type>::type &composite::as() const
{
    accessor<typename decay_deduce<T>::type> a;
    return a(std::get<typename decay_deduce<T>::type>(d_data));
}

}
