//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_PSL_VERSION_ERROR_HPP
#define BOOST_RTS_PSL_VERSION_ERROR_HPP

#include <boost/rts/detail/config.hpp>
#include <stdexcept>

namespace boost {
namespace rts {
namespace psl {

class version_error
    : public std::logic_error
{
public:
    BOOST_RTS_DECL
    version_error();
};

} // psl
} // rts
} // boost

#endif
