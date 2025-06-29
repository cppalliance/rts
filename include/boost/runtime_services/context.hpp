//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/runtime_services
//

#ifndef BOOST_RUNTIME_SERVICES_CONTEXT_HPP
#define BOOST_RUNTIME_SERVICES_CONTEXT_HPP

#include <boost/runtime_services/detail/config.hpp>
#include <boost/runtime_services/service.hpp>
#include <boost/runtime_services/detail/type_index.hpp>
#include <memory>

namespace boost {
namespace runtime_services {

class context
{
    struct data;

public:
    context(context const&) = delete;
    context& operator=(
        context const&) = delete;

    /** Destructor.
    */
    BOOST_RUNTIME_SERVICES_DECL
    ~context();

    /** Constructor.
    */
    BOOST_RUNTIME_SERVICES_DECL
    context();

    //--------------------------------------------

    /** Create a service.

        The service must not already exist.

        @par Exception Safety
        Strong guarantee.
        Calls to allocate may throw.

        @throw std::invalid_argument `find_service<T> != nullptr`

        @return A reference to the new service.

        @tparam T The service type.

        @param args Arguments forwarded to the
        service constructor.
    */
    template<
        class T,
        class... Args>
    T&
    make_service(
        Args&&... args);

    /** Return an existing service

        The function returns `nullptr` if the
        service does not exist.

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @return A pointer to the service,
        or `nullptr`.

        @tparam T The service type.
    */
    template<class T>
    T*
    find_service() const noexcept;

    /** Return true if a service exists

        @par Effects
        @code
        return this->find_service<T>() != nullptr;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @return `true` if the service exists.

        @tparam T The service type.
    */
    template<class T>
    bool
    has_service() const noexcept;

    /** Return a reference to an existing service

        The service must exist, or else an
        exception is thrown.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `find_service<T> == nullptr`.

        @return A reference to the service.

        @tparam T The service type.
    */
    template<class T>
    T&
    get_service() const;

private:
    BOOST_RUNTIME_SERVICES_DECL
    service*
    find_service_impl(
        detail::type_index ti) const noexcept;

    BOOST_RUNTIME_SERVICES_DECL
    service&
    make_service_impl(
        detail::type_index ti,
        std::unique_ptr<service> sp);

    std::unique_ptr<data> p_;
};

} // runtime_services
} // boost

#include <boost/runtime_services/impl/context.hpp>

#endif
