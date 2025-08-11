//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/psl/version_error.hpp>

namespace boost {
namespace rts {
namespace psl {

version_error::
version_error()
    : std::logic_error(
        "function not supported in this version")
{
}

} // psl
} // rts
} // boost
