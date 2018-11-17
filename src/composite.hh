#pragma once

#include <variant>
#include <string>
#include "types.hh"
#include "deduce.hh"

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
    constexpr const typename decay_deduce<T>::type &as() const;

private:
    std::variant<
        none,
        bool,
        int64_t,
        double,
        std::string,
        sequence,
        mapping
    > d_data;
};

template <typename T>
constexpr bool composite::is() const noexcept
{
    return std::holds_alternative<typename decay_deduce<T>::type>(d_data);
}

template <typename T>
constexpr const typename decay_deduce<T>::type &composite::as() const
{
    return std::get<typename decay_deduce<T>::type>(d_data);
}

}
