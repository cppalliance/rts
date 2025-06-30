//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2024 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_ZLIB_IMPL_ERROR_HPP
#define BOOST_RTS_ZLIB_IMPL_ERROR_HPP

#include <boost/rts/detail/config.hpp>

#include <boost/system/error_category.hpp>
#include <boost/system/is_error_code_enum.hpp>

namespace boost {

namespace system {
template<>
struct is_error_code_enum<
    ::boost::rts::zlib::error>
{
    static bool const value = true;
};
} // system

namespace rts {
namespace zlib {

namespace detail {

struct BOOST_SYMBOL_VISIBLE
    error_cat_type
    : system::error_category
{
    BOOST_RTS_DECL const char* name(
        ) const noexcept override;
    BOOST_RTS_DECL bool failed(
        int) const noexcept override;
    BOOST_RTS_DECL std::string message(
        int) const override;
    BOOST_RTS_DECL char const* message(
        int, char*, std::size_t
            ) const noexcept override;
    BOOST_SYSTEM_CONSTEXPR error_cat_type()
        : error_category(0xe6c6d0215d1d6e22)
    {
    }
};

BOOST_RTS_DECL extern
    error_cat_type error_cat;

} // detail

inline
BOOST_SYSTEM_CONSTEXPR
system::error_code
make_error_code(
    error ev) noexcept
{
    return system::error_code{
        static_cast<std::underlying_type<
            error>::type>(ev),
        detail::error_cat};
}

} // zlib
} // rts
} // boost

#endif
