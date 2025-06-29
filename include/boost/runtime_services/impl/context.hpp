//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/runtime_services
//

#ifndef BOOST_RUNTIME_SERVICES_IMPL_CONTEXT_HPP
#define BOOST_RUNTIME_SERVICES_IMPL_CONTEXT_HPP

#include <boost/runtime_services/detail/type_index.hpp>

#include <boost/mp11/utility.hpp>

namespace boost {
namespace runtime_services {

namespace detail {

template<class T>
using get_key_impl =
    typename T::key_type;

template<class T>
using get_key_type =
    mp11::mp_eval_or<T, get_key_impl, T>;

} // detail

//------------------------------------------------

template<class T, class... Args>
T&
context::
make_service(
    Args&&... args)
{
    static_assert(
        std::is_base_of<service, T>::value,
        "Type requirements not met.");

    auto const ti = detail::get_type_index<
        detail::get_key_type<T>>();
    auto const ps = find_service_impl(ti);
    if(ps)
        BOOST_THROW_EXCEPTION(
            std::invalid_argument("service exists"));
    return detail::downcast<T&>(
        make_service_impl(ti,
            std::unique_ptr<service>(
                new T(*this, std::forward<
                    Args>(args)...))));
}

template<class T>
T*
context::
find_service() const noexcept
{
    auto const ti = detail::get_type_index<
        detail::get_key_type<T>>();
    auto const ps = find_service_impl(ti);
    if(! ps)
        return nullptr;
    return detail::downcast<T*>(ps);
}

template<class T>
bool
context::
has_service() const noexcept
{
    return find_service<T>() != nullptr;
}

template<class T>
T&
context::
get_service() const
{
    auto ps = find_service<T>();
    if(! ps)
        BOOST_THROW_EXCEPTION(
            std::invalid_argument("service not found"));
    return *ps;
}

} // runtime_services
} // boost

#endif
