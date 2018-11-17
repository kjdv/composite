#pragma once

#include <variant>
#include <string>
#include "types.hh"

namespace composite {

class composite {
public:
    constexpr explicit composite() noexcept
        : d_data{none{}}
    {}

    template <typename T>
    constexpr bool is() const noexcept;

    template <typename T>
    constexpr const T &as() const;

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
    return std::holds_alternative<T>(d_data);
}

template <typename T>
constexpr const T &composite::as() const
{
    return std::get<T>(d_data);
}

}
