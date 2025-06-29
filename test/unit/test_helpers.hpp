//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/runtime_services
//

#ifndef BOOST_RUNTIME_SERVICES_TEST_HELPERS_HPP
#define BOOST_RUNTIME_SERVICES_TEST_HELPERS_HPP

// Trick boostdep into requiring URL
// since we need it for the unit tests
#ifdef BOOST_RUNTIME_SERVICES_BOOSTDEP
#include <boost/url/url.hpp>
#endif

#include "test_suite.hpp"

namespace boost {
namespace runtime_services {

} // runtime_services
} // boost

#endif
