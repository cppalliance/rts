//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_SERVICE_SERVICE_HPP
#define BOOST_RTS_SERVICE_SERVICE_HPP

#include <boost/rts/detail/config.hpp>

namespace boost {
namespace rts {

#ifndef BOOST_RTS_DOCS
class services;
#endif

/** Base class for all services
*/
struct BOOST_SYMBOL_VISIBLE
    service
{
    BOOST_RTS_DECL
    virtual
    ~service() = 0;

#if 0
protected:
    /** Called to perform two-phase initialization
    */
    virtual
    void
    start() = 0;
#endif

private:
    friend class services;
};

} // rts
} // boost

#endif
