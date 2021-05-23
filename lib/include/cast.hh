#pragma once

#include "types.hh"
#include "deduce.hh"
#include <stdexcept>
#include <type_traits>
#include <string>
#include <sstream>

namespace composite {

namespace implementation {

template <typename To>
To cast(none)
{
    return To{};
}

template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
To cast(bool value)
{
  return static_cast<To>(value);
}

template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
To cast(bool)
{
  throw std::bad_cast();
}

template<>
std::string cast<std::string>(bool value);

template <>
none cast<none>(bool);

template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
To cast(int64_t value)
{
    return static_cast<To>(value);
}

template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
To cast(int64_t)
{
    throw std::bad_cast();
}

template<>
std::string cast<std::string>(int64_t value);

template <>
none cast<none>(int64_t);

template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
To cast(uint64_t value)
{
    return static_cast<To>(value);
}

template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
To cast(uint64_t)
{
    throw std::bad_cast();
}

template<>
std::string cast<std::string>(uint64_t value);

template <>
none cast<none>(uint64_t);

template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
To cast(double value)
{
    return static_cast<To>(value);
}

template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
To cast(double)
{
    throw std::bad_cast();
}

template<>
std::string cast<std::string>(double value);

template <>
none cast<none>(double);

std::string sanitize(std::string_view value);

template <typename To, std::enable_if_t<std::is_arithmetic<To>::value && !std::is_same<typename deduce<To>::type, bool>::value, int> = 0>
To cast(const std::string  &value)
{
    std::istringstream stream(value);

    To r;
    if (stream >> r)
      return r;
    throw std::bad_cast();
}

template <typename To, std::enable_if_t<std::is_same<typename deduce<To>::type, bool>::value, int> = 0>
To cast(const std::string &value)
{
    auto input = sanitize(value);

    for(std::string_view key : {"true", "yes", "t", "y"}) // positive
    {
      if(input.compare(0, key.size(), key) == 0)
        return true;
    }

    for(std::string_view key : {"false", "no", "f", "n"}) // negative
    {
      if(input.compare(0, key.size(), key) == 0)
        return false;
    }

    return static_cast<bool>(cast<int>(input));
}

template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
To cast(const std::string &)
{
    throw std::bad_cast();
}

template<>
std::string cast<std::string>(const std::string &value);

template <>
none cast<none>(const std::string &);

template<typename To>
To cast(const sequence &)
{
    throw std::bad_cast();
}

template<>
::composite::sequence cast<::composite::sequence>(const sequence &s);

template<>
none cast<none>(const sequence &);

template<>
std::string cast<std::string>(const sequence &s);

template<typename To>
To cast(const mapping &)
{
   throw std::bad_cast();
}

template<>
none cast<none>(const mapping &);

template<>
std::string cast<std::string>(const mapping &m);

template<>
::composite::mapping cast<::composite::mapping>(const mapping &m);

}

template <typename To, typename From>
To cast(const From &value)
{
  //implementation::caster<From> c{};
  return implementation::cast<To>(value);
}


}
