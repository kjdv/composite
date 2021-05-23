#pragma once

#include "types.hh"
#include <type_traits>
#include <string>
#include <string_view>

namespace composite {

template <typename T, typename U = void>
struct deduce
{};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_void_v<T> || std::is_same_v<T, none>>>
{
    using type = none;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_same_v<bool, T>>>
{
    using type = bool;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_integral_v<T> && !std::is_unsigned_v<T> && !std::is_same_v<bool, T>>>
{
    using type = int64_t;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T> && !std::is_same_v<bool, T>>>
{
    using type = uint64_t;
};


template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_floating_point_v<T>>>
{
    using type = double;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_convertible_v<T, std::string> || std::is_same_v<T, std::string_view>>>
{
    using type = std::string;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_same_v<T, sequence>>>
{
    using type = sequence;
};

template <typename T>
struct deduce<T, typename std::enable_if_t<std::is_same_v<T, mapping>>>
{
    using type = implementation::mapping;
};

template <typename T>
struct decay_deduce : public deduce<typename std::decay_t<T>>
{
};

using void_t = deduce<void>::type;
using bool_t = deduce<bool>::type;
using int_t = deduce<int>::type;
using uint_t = deduce<unsigned>::type;
using float_t = deduce<float>::type;
using string_t = deduce<std::string>::type;

} // namespace composite
