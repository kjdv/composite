#pragma once

#include "composite.hh"

namespace composite {

class bad_access : public std::bad_variant_access
{
public:
    explicit bad_access(std::string_view msg) noexcept
        : d_msg(msg)
    {}

    const char* what() const noexcept override
    {
        return d_msg.c_str();
    }

private:
    std::string d_msg;
};

constexpr const composite& access(const composite& c) noexcept;

template <typename... Tail>
const composite& access(const composite& c, std::size_t idx, Tail&&... tail);

template <typename... Tail>
const composite& access(const composite& c, std::string_view key, Tail&&... tail);

constexpr inline const composite& access(const composite& c) noexcept
{
    return c;
}

template <typename... Tail>
const composite& access(const composite& c, std::size_t idx, Tail&&... tail)
{
    if(!c.is<sequence>())
        throw bad_access("not a sequence");

    auto& s = c.as<sequence>();

    if(idx >= s.size())
        throw bad_access("index out of range");

    return access(s[idx], std::forward<Tail>(tail)...);
}

template <typename... Tail>
const composite& access(const composite& c, std::string_view key, Tail&&... tail)
{
    if(!c.is<mapping>())
        throw bad_access("not a mapping");

    auto& m  = c.as<mapping>();
    auto  it = m.find(mapping::key_type(key));

    if(it == m.end())
        throw bad_access("key not found in map");

    return access(it->second, std::forward<Tail>(tail)...);
}

} // namespace composite
