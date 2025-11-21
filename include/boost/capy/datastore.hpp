//
// Copyright (c) 2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#ifndef BOOST_CAPY_DATASTORE_HPP
#define BOOST_CAPY_DATASTORE_HPP

#include <boost/capy/detail/config.hpp>
#include <boost/capy/polystore.hpp>

namespace boost {
namespace capy {

class datastore : public polystore
{
public:
    datastore() = default;

    void clear() noexcept  
    {
        polystore::clear();
    }
};

} // capy
} // boost

#endif
