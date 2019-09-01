#pragma once

#include "types.hh"
#include "deduce.hh"
#include <stdexcept>
#include <type_traits>
#include <string>
#include <sstream>

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
    return To{};
  }
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

template <>
struct caster<double>
{
  template <typename To, std::enable_if_t<std::is_arithmetic<To>::value, int> = 0>
  To cast(double value) const
  {
    return static_cast<To>(value);
  }

  template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
  To cast(double) const
  {
    throw std::bad_cast();
  }

  template<>
  std::string cast<std::string>(double value) const;

  template <>
  none cast<none>(double) const;
};

template <>
struct caster<std::string>
{
private:
  std::string sanitize(std::string_view value) const;
public:

  template <typename To, std::enable_if_t<std::is_same<typename deduce<To>::type, bool>::value, int> = 0>
  To cast(const std::string &value) const
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

  template <typename To, std::enable_if_t<std::is_arithmetic<To>::value && !std::is_same<typename deduce<To>::type, bool>::value, int> = 0>
  To cast(const std::string  &value) const
  {
    std::istringstream stream(value);

    To r;
    if (stream >> r)
      return r;
    throw std::bad_cast();
  }

  template <typename To, std::enable_if_t<!std::is_arithmetic<To>::value, int> = 0>
  To cast(const std::string &) const
  {
    throw std::bad_cast();
  }

  template<>
  std::string cast<std::string>(const std::string &value) const;

  template <>
  none cast<none>(const std::string &) const;
};

template<>
struct caster<::composite::sequence>
{
  template<typename To>
  To cast(const sequence &) const
  {
    throw std::bad_cast();
  }

  template<>
  none cast<none>(const sequence &) const;

  template<>
  std::string cast<std::string>(const sequence &s) const;
};

template<>
struct caster<mapping>
{
  template<typename To>
  To cast(const mapping &) const
  {
    throw std::bad_cast();
  }

  template<>
  none cast<none>(const mapping &) const;

  template<>
  std::string cast<std::string>(const mapping &m) const;
};


}

template <typename To, typename From>
To cast(const From &value)
{
  implementation::caster<From> c{};
  return c.template cast<To>(value);
}


}
