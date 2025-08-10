//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/context.hpp>
#include <boost/rts/zlib.hpp>

#include "test_helpers.hpp"

namespace boost {
namespace rts {

struct zlib_test
{
    void
    test_error_code()
    {
        // TODO
        boost::system::error_code ec{ zlib::error::buf_err };
    }

    void
    test_deflate()
    {
        // TODO
        context ctx;
        zlib::install_deflate_service(ctx);
    }

    void
    test_inflate()
    {
        // TODO
        context ctx;
        zlib::install_inflate_service(ctx);
    }

    void
    run()
    {
        test_error_code();
    #ifdef BOOST_RTS_HAS_ZLIB
        test_deflate();
        test_inflate();
    #endif
    }
};

TEST_SUITE(zlib_test, "boost.rts.zlib");

} // namespace rts
} // namespace boost
