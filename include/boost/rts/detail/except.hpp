//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_DETAIL_EXCEPT_HPP
#define BOOST_RTS_DETAIL_EXCEPT_HPP

#include <boost/rts/detail/config.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/core/detail/string_view.hpp>

namespace boost {
namespace rts {
namespace detail {

BOOST_RTS_DECL void BOOST_NORETURN throw_bad_typeid(
    source_location const& loc = BOOST_CURRENT_LOCATION);

BOOST_RTS_DECL void BOOST_NORETURN throw_invalid_argument(
    core::string_view s = "invalid argument",
    source_location const& loc = BOOST_CURRENT_LOCATION);

BOOST_RTS_DECL void BOOST_NORETURN throw_logic_error(
    core::string_view s = "logic error",
    source_location const& loc = BOOST_CURRENT_LOCATION);

} // detail
} // rts
} // boost

#endif
