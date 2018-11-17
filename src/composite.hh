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
    constexpr explicit composite(T&& value) noexcept;

    template <typename T>
    constexpr bool is() const noexcept;

    template <typename T>
    constexpr const typename accessor<typename decay_deduce<T>::type>::type &as() const;

    template <typename V>
    decltype(auto) visit(V&& visitor) const;

private:
    friend bool operator==(const composite &, const composite &) noexcept;
    friend std::size_t hash(const composite &) noexcept;

    using variant_t = std::variant<
        deduce<none>::type,
        deduce<bool>::type,
        deduce<int>::type,
        deduce<double>::type,
        deduce<std::string>::type,
        deduce<sequence>::type,
        implementation::mapping // small kludge, composite::mapping is an incomplete type at this point
    >;

    variant_t d_data;
};

bool operator==(const composite &a, const composite &b) noexcept;

inline bool operator!=(const composite &a, const composite &b) noexcept
{
    return !(a == b);
}

std::ostream &operator<<(std::ostream &o, const composite &c) noexcept;

template <typename T, typename U>
constexpr composite::composite(T&& value) noexcept
    : d_data(std::in_place_type<U>, std::forward<T>(value))
{}

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

template <typename V>
decltype(auto) composite::visit(V&& visitor) const
{
    return std::visit(visitor, d_data);
}

std::size_t hash(const composite &c) noexcept;

}

namespace std {

template <>
struct hash<composite::composite>
{
    typedef composite::composite argument_type;
    typedef std::size_t result_type;
    result_type operator()(const argument_type &c) const noexcept
    {
        return composite::hash(c);
    }
};

}
