#include "composite.hh"

namespace composite {

bool operator==(const composite &a, const composite &b) noexcept
{
    return a.d_data == b.d_data;
}

}
