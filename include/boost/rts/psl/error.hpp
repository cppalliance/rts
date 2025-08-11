//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_PSL_ERROR_HPP
#define BOOST_RTS_PSL_ERROR_HPP

namespace boost {
namespace rts {
namespace psl {

/** Error codes returned from PSL functions.

    Negative return codes mean failure.
    Positive values are reserved for non-error return codes.
*/
enum error
{
	success = 0,
	err_invalid_arg = -1,
	err_converter = -2,
	err_to_utf16 = -3,
	err_to_lower = -4,
	err_to_utf8 = -5,
	err_no_mem = -6
};

} // psl
} // rts
} // boost

#endif
