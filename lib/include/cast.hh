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
  To cast(const none &) const
  {
    throw std::bad_cast();
  }

  template<>
  none cast<none>(const none &) const
  {
    return none{};
  }

  template<>
  std::string cast<std::string>(const none &) const
  {
    return "<none>";
  }
};

template <>
struct caster<int64_t>
{
  template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
  To cast(const int64_t &value) const
  {
    return static_cast<To>(value);
  }

  template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
  To cast(const int64_t &) const
  {
    throw std::bad_cast();
  }

  template<>
  std::string cast<std::string>(const int64_t &value) const
  {
    return std::to_string(value);
  }

  template <>
  none cast<none>(const int64_t &) const
  {
    return none{};
  }
};

}

template <typename To, typename From>
To cast(const From &value)
{
  implementation::caster<From> c{};
  return c.template cast<To>(value);
}


}
