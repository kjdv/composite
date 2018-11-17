#include "types.hh"

#include <iostream>

namespace composite {

std::ostream &operator<<(std::ostream &o, none)
{
    return o << "<none>";
}

}
