#pragma once

#include "types.hh"
#include <type_traits>
#include <string_view>

namespace composite {

template <typename T, typename U = void>
struct deduce
{
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_void<T>::value || std::is_same<T, none>::value>::type>
{
    using type = none;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
    using type = bool;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
{
    using type = int64_t;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    using type = double;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_convertible<T, std::string>::value || std::is_same<T, std::string_view>::value>::type>
{
    using type = std::string;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_same<T, sequence>::value>::type>
{
    using type = sequence;
};

template <typename T>
struct deduce<T, typename std::enable_if<std::is_same<T, mapping>::value>::type>
{
    using type = implementation::mapping;
};

template <typename T>
struct decay_deduce : public deduce<typename std::decay<T>::type>
{
};

} // namespace composite
