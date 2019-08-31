#pragma once

#include "deduce.hh"
#include "traits.hh"
#include "types.hh"
#include "cast.hh"
#include <string>
#include <variant>

namespace composite {

class composite
{
public:
    constexpr explicit composite() noexcept
        : d_data{none{}}
    {}

    template <typename T, typename U = typename decay_deduce<T>::type>
    constexpr explicit composite(T value) noexcept;

    template <typename T>
    constexpr bool is() const noexcept;

    template <typename T>
    constexpr const typename accessor<typename decay_deduce<T>::type>::type& as() const;

    template <typename T>
    constexpr typename decay_deduce<T>::type to() const;

    // straightforward (non-recursive) visitor
    template <typename V>
    auto visit(V&& visitor) const;

private:
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

bool operator==(const composite& a, const composite& b) noexcept;

inline bool operator!=(const composite& a, const composite& b) noexcept
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, const composite& c) noexcept;

template <typename T, typename U>
constexpr composite::composite(T value) noexcept
    : d_data(std::in_place_type<U>, std::move(value))
{}

template <typename T>
constexpr bool composite::is() const noexcept
{
    return std::holds_alternative<typename decay_deduce<T>::type>(d_data);
}

template <typename T>
constexpr const typename accessor<typename decay_deduce<T>::type>::type& composite::as() const
{
    accessor<typename decay_deduce<T>::type> a;
    return a(std::get<typename decay_deduce<T>::type>(d_data));
}

/*
template <typename T>
constexpr typename decay_deduce<T>::type composite::to() const
{
  using To = typename decay_deduce<T>::type;
  return std::visit([](auto&& value) {
    using From = std::decay_t<decltype(value)>;
    return caster<From, To>{}(value);
  }, d_data);
}*/

template <typename V>
auto composite::visit(V&& visitor) const
{
    auto wrapped = [&visitor](auto&& v) {
        using T = std::decay_t<decltype(v)>;
        accessor<T> acc;
        return visitor(acc(v));
    };
    return std::visit(wrapped, d_data);
}

} // namespace composite
