//
// Copyright (c) 2022 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/beast2
//

#include <boost/rts/application.hpp>
#include <boost/rts/detail/except.hpp>
#include <mutex>
#include <vector>

namespace boost {
namespace rts {

enum application::state : char
{
    none,
    starting,
    running,
    stopping,
    stopped
};

struct application::impl
{
    std::mutex m;
    state st = state::none;
};

application::
~application()
{
    {
        std::lock_guard<std::mutex> lock(impl_->m);
        if( impl_->st != state::stopped &&
            impl_->st != state::none)
        {
            // stop() hasn't returned yet
            detail::throw_invalid_argument();
        }
    }
    delete impl_;
}

application::
application()
    : impl_(new impl)
{
}

void
application::
start()
{
    {
        std::lock_guard<std::mutex> lock(impl_->m);
        if(impl_->st != state::none)
        {
            // can't call twice
            detail::throw_invalid_argument();
        }
        impl_->st = state::starting;
    }
    auto v = get_elements();
    for(std::size_t i = 0; i < v.size(); ++i)
    {
        try
        {
            v[i].start();
        }
        catch(std::exception const&)
        {
            {
                std::lock_guard<std::mutex> lock(impl_->m);
                impl_->st = state::stopping;
            }
            do
            {
                v[i].stop();
            }
            while(i-- != 0);
            {
                std::lock_guard<std::mutex> lock(impl_->m);
                impl_->st = state::stopped;
            }
            throw;
        }
    }
    {
        std::lock_guard<std::mutex> lock(impl_->m);
        impl_->st = state::running;
    }
}

void
application::
stop()
{
    {
        std::lock_guard<std::mutex> lock(impl_->m);
        if(impl_->st != state::running)
            detail::throw_invalid_argument();
        impl_->st = state::stopping;
    }

    auto v = get_elements();
    for(std::size_t i = v.size(); i--;)
        v[i].stop();

    {
        std::lock_guard<std::mutex> lock(impl_->m);
        impl_->st = state::stopped;
    }
}

} // rts
} // boost
