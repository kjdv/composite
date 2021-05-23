#include <cast.hh>
#include <sstream>
#include <composite.hh>

namespace composite {
namespace implementation {

template<>
std::string cast<std::string>(bool value)
{
  return value ? "true" : "false";
}

template <>
none cast<none>(bool)
{
  return none{};
}

template<>
std::string cast<std::string>(int64_t value)
{
  return std::to_string(value);
}

template <>
none cast<none>(int64_t)
{
  return none{};
}

template<>
std::string cast<std::string>(uint64_t value)
{
  return std::to_string(value);
}

template <>
none cast<none>(uint64_t)
{
  return none{};
}


template<>
std::string cast<std::string>(double value)
{
  return std::to_string(value);
}

template <>
none cast<none>(double)
{
  return none{};
}

template<>
std::string cast<std::string>(const std::string &value)
{
  return value;
}

template <>
none cast<none>(const std::string &)
{
  return none{};
}

std::string sanitize(std::string_view input)
{
  std::string sanitized;
  for(char c : input)
  {
    if(isalnum(c)) // ignore non-alpha (ws), and convert to lower case
      sanitized += tolower(c);
  }
  return sanitized;
}

template<>
none cast<none>(const sequence &)
{
  return none{};
}

template<>
std::string cast<std::string>(const sequence &s)
{
  std::ostringstream stream;
  stream << s;
  return stream.str();
}

template<>
::composite::sequence cast<::composite::sequence>(const sequence &s)
{
  return s;
}

template<>
none cast<none>(const mapping &)
{
  return none{};
}

template<>
std::string cast<std::string>(const mapping &m)
{
  std::ostringstream stream;
  stream << m.access();
  return stream.str();
}


template<>
::composite::mapping cast<::composite::mapping>(const mapping &m)
{
  return m.access();
}

}
}
