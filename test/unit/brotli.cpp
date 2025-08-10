//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/brotli.hpp>
#include <boost/rts/context.hpp>

#include "test_helpers.hpp"

namespace boost {
namespace rts {

struct brotli_test
{
    void
    test_error_code()
    {
        // TODO
        boost::system::error_code ec{ brotli::error::no_error };
    }

    void
    test_decode()
    {
        // TODO
        context ctx;
        brotli::install_decode_service(ctx);
    }

    void
    test_encode()
    {
        // TODO
        context ctx;
        brotli::install_encode_service(ctx);
    }

    void
    run()
    {
        test_error_code();
    #ifdef BOOST_RTS_HAS_BROTLI
        test_decode();
        test_encode();
    #endif
    }
};

TEST_SUITE(brotli_test, "boost.rts.brotli");

} // namespace rts
} // namespace boost
