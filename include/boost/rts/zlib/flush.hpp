//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_ZLIB_FLUSH_HPP
#define BOOST_RTS_ZLIB_FLUSH_HPP

namespace boost {
namespace rts {
namespace zlib {

/// Flush methods
enum flush
{
    no_flush      = 0,
    partial_flush = 1,
    sync_flush    = 2,
    full_flush    = 3,
    finish        = 4,
    block         = 5,
    trees         = 6
};

} // zlib
} // rts
} // boost

#endif
