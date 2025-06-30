//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_ZLIB_COMPRESSION_STRATEGY_HPP
#define BOOST_RTS_ZLIB_COMPRESSION_STRATEGY_HPP

namespace boost {
namespace rts {
namespace zlib {

/// Compression strategy
enum compression_strategy
{
    default_strategy = 0,
    filtered         = 1,
    huffman_only     = 2,
    rle              = 3,
    fixed            = 4
};

} // zlib
} // rts
} // boost

#endif
