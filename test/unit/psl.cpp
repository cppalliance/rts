//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/psl.hpp>
#include <boost/rts/context.hpp>

#include "test_helpers.hpp"

namespace boost {
namespace rts {

struct psl_test
{
    void
    test_service()
    {
        // TODO
        context ctx;
        psl::install_service(ctx);
    }

    void
    run()
    {
    #ifdef BOOST_RTS_HAS_PSL
        test_service();
    #endif
    }
};

TEST_SUITE(psl_test, "boost.rts.psl");

} // namespace rts
} // namespace boost
