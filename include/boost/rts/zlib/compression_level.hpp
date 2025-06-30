//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_ZLIB_COMPRESSION_LEVEL_HPP
#define BOOST_RTS_ZLIB_COMPRESSION_LEVEL_HPP

namespace boost {
namespace rts {
namespace zlib {

/// Compression levels
enum compression_level
{
    default_compression = -1,
    no_compression      = 0,
    best_speed          = 1,
    best_compression    = 9
};

} // zlib
} // rts
} // boost

#endif
