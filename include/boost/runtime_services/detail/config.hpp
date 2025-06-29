//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/runtime_services
//

#ifndef BOOST_RUNTIME_SERVICES_DETAIL_CONFIG_HPP
#define BOOST_RUNTIME_SERVICES_DETAIL_CONFIG_HPP

#include <boost/config.hpp>

namespace boost {
namespace runtime_services {

//------------------------------------------------

# if (defined(BOOST_RUNTIME_SERVICES_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_RUNTIME_SERVICES_STATIC_LINK)
#  if defined(BOOST_RUNTIME_SERVICES_SOURCE)
#   define BOOST_RUNTIME_SERVICES_DECL        BOOST_SYMBOL_EXPORT
#   define BOOST_RUNTIME_SERVICES_BUILD_DLL
#  else
#   define BOOST_RUNTIME_SERVICES_DECL        BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib

# ifndef  BOOST_RUNTIME_SERVICES_DECL
#  define BOOST_RUNTIME_SERVICES_DECL
# endif

# if !defined(BOOST_RUNTIME_SERVICES_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_RUNTIME_SERVICES_NO_LIB)
#  define BOOST_LIB_NAME boost_runtime_services
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_RUNTIME_SERVICES_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif

//------------------------------------------------

#if defined(BOOST_NO_CXX14_AGGREGATE_NSDMI) || defined(BOOST_MSVC)
# define BOOST_RUNTIME_SERVICES_AGGREGATE_WORKAROUND
#endif

// Add source location to error codes
#ifdef BOOST_RUNTIME_SERVICES_NO_SOURCE_LOCATION
# define BOOST_RUNTIME_SERVICES_ERR(ev) (::boost::system::error_code(ev))
# define BOOST_RUNTIME_SERVICES_RETURN_EC(ev) return (ev)
#else
# define BOOST_RUNTIME_SERVICES_ERR(ev) ( \
    ::boost::system::error_code( (ev), [] { \
    static constexpr auto loc((BOOST_CURRENT_LOCATION)); \
    return &loc; }()))
# define BOOST_RUNTIME_SERVICES_RETURN_EC(ev) \
    static constexpr auto loc ## __LINE__((BOOST_CURRENT_LOCATION)); \
    return ::boost::system::error_code((ev), &loc ## __LINE__)
#endif

//------------------------------------------------

// avoid all of Boost.TypeTraits for just this
template<class...> struct make_void { typedef void type; };
template<class... Ts> using void_t = typename make_void<Ts...>::type;

} // runtime_services
} // boost

#endif
