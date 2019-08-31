#include <cast.hh>

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

}
}
