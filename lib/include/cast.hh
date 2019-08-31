#pragma once

#include "types.hh"
#include "deduce.hh"
#include <stdexcept>
#include <type_traits>
#include <string>

namespace composite {

namespace implementation {

template <typename From>
struct caster
{
  template <typename To>
  To operator()(const From &) const
  {
    throw std::bad_cast();
  }
};

template <>
struct caster<none>
{
  template <typename To>
  To cast(none) const
  {
    throw std::bad_cast();
  }

  template<>
  none cast<none>(none) const;

  template<>
  std::string cast<std::string>(none) const;
};

template <>
struct caster<bool>
{
  template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
  To cast(bool value) const
  {
    return static_cast<To>(value);
  }

  template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
  To cast(bool) const
  {
    throw std::bad_cast();
  }

  template<>
  std::string cast<std::string>(bool value) const;

  template <>
  none cast<none>(bool) const;
};

template <>
struct caster<int64_t>
{
  template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
  To cast(int64_t value) const
  {
    return static_cast<To>(value);
  }

  template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
  To cast(int64_t) const
  {
    throw std::bad_cast();
  }

  template<>
  std::string cast<std::string>(int64_t value) const;

  template <>
  none cast<none>(int64_t) const;
};

}

template <typename To, typename From>
To cast(const From &value)
{
  implementation::caster<From> c{};
  return c.template cast<To>(value);
}


}
