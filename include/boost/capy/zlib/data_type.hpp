//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#ifndef BOOST_CAPY_ZLIB_DATA_TYPE_HPP
#define BOOST_CAPY_ZLIB_DATA_TYPE_HPP

namespace boost {
namespace capy {
namespace zlib {

/// Possible values of the data_type field for deflate
enum data_type
{
    binary  = 0,
    text    = 1,
    ascii   = 1,
    unknown = 2
};

} // zlib
} // capy
} // boost

#endif
