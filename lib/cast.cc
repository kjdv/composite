#include <cast.hh>
#include <sstream>
#include <composite.hh>

namespace composite {
namespace implementation {

template<>
none caster<none>::cast<none>(none) const
{
  return none{};
}

template<>
std::string caster<none>::cast<std::string>(none) const
{
  return "<none>";
}

template<>
std::string caster<bool>::cast<std::string>(bool value) const
{
  return value ? "true" : "false";
}

template <>
none caster<bool>::cast<none>(bool) const
{
  return none{};
}

template<>
std::string caster<int64_t>::cast<std::string>(int64_t value) const
{
  return std::to_string(value);
}

template <>
none caster<int64_t>::cast<none>(int64_t) const
{
  return none{};
}

template<>
std::string caster<double>::cast<std::string>(double value) const
{
  return std::to_string(value);
}

template <>
none caster<double>::cast<none>(double) const
{
  return none{};
}

template<>
std::string caster<std::string>::cast<std::string>(const std::string &value) const
{
  return value;
}

template <>
none caster<std::string>::cast<none>(const std::string &) const
{
  return none{};
}

std::string caster<std::string>::sanitize(std::string_view input) const
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
none caster<::composite::sequence>::cast<none>(const sequence &) const
{
  return none{};
}

template<>
std::string caster<::composite::sequence>::cast<std::string>(const sequence &s) const
{
  std::ostringstream stream;
  stream << s;
  return stream.str();
}

template<>
none caster<mapping>::cast<none>(const mapping &) const
{
  return none{};
}

template<>
std::string caster<mapping>::cast<std::string>(const mapping &m) const
{
  std::ostringstream stream;
  stream << m.access();
  return stream.str();
}


}
}
