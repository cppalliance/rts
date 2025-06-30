//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/context.hpp>
//#include <boost/unordered_map.hpp> // doesn't support heterogenous lookup yet
#include <unordered_map>

namespace boost {
namespace rts {

struct context::data
{
    // Installed services
    std::unordered_map<
        detail::type_index,
        std::unique_ptr<service>,
        detail::type_index_hasher
            > services;
};

//------------------------------------------------

context::
~context()
{
}

context::
context()
    : p_(new data)
{
}

//------------------------------------------------

auto
context::
find_service_impl(
    detail::type_index id) const noexcept ->
        service*
{
    auto it = p_->services.find(id);
    if(it != p_->services.end())
        return it->second.get();
    return nullptr;
}

auto
context::
make_service_impl(
    detail::type_index id,
    std::unique_ptr<service> sp) ->
        service&
{
    auto const result =
        p_->services.emplace(
            id, std::move(sp));
    if(! result.second)
    {
        // already exists
        BOOST_THROW_EXCEPTION(
            std::out_of_range("out of range"));
    }
    return *result.first->second;
}

} // rts
} // boost
