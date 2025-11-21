//
// Copyright (c) 2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

// Test that header file is self-contained.
#include <boost/capy/datastore.hpp>

#include "test_suite.hpp"

namespace boost {
namespace capy {

struct datastore_test
{
    void run()
    {
        struct T{};

        datastore ds; 
        BOOST_TEST_EQ( ds.find<T>(), nullptr );
        BOOST_TEST_NO_THROW( ds.emplace<T>() );
        BOOST_TEST_NE( ds.find<T>(), nullptr );
        ds.clear();
        BOOST_TEST_EQ( ds.find<T>(), nullptr );
    }
};

TEST_SUITE(datastore_test, "boost.capy.datastore");

} // capy
} // boost
