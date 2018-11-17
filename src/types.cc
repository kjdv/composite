#include "types.hh"
#include "composite.hh"

#include <iostream>

namespace composite {

std::ostream &operator<<(std::ostream &o, none)
{
    return o << "<none>";
}

namespace implementation {

const ::composite::mapping &implementation::mapping::access() const
{
    return std::any_cast<const ::composite::mapping &>(d_impl);
}

bool operator==(const mapping &a, const mapping &b) noexcept
{
    accessor<mapping> acc;
    return acc(a) == acc(b);
}

}

}
