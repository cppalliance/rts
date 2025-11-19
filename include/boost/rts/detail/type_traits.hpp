//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_RTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost {
namespace rts {
namespace detail {

template<class...> struct make_void { typedef void type; };
template<class... Ts> using void_t = typename make_void<Ts...>::type;

template<class Base, class Derived>
using derived_from = std::integral_constant<bool,
    std::is_base_of<Base, Derived>::value &&
    std::is_convertible<
        Derived const volatile*,
        Base const volatile*>::value>;

template<bool...> struct bool_pack {};
template<bool... Bs>
struct all_true : std::is_same<bool_pack<
    true, Bs...>, bool_pack<Bs..., true>> {};

} // detail
} // rts
} // boost

#endif
