#pragma once

#include <type_traits>
#include "types.hh"

namespace composite {

template <typename T, typename = std::enable_if<std::is_void<T>::value || std::is_same<T, none>::value>>
struct deduce
{
    using type = none;
};

template <typename T>
struct decay_deduce : public deduce<typename std::decay<T>::type>
{};

}
