#include <access.hh>

namespace composite {

bad_access::bad_access(std::string_view msg) noexcept
    : d_msg(msg)
{}

const char* bad_access::what() const noexcept
{
    return d_msg.c_str();
}


}
