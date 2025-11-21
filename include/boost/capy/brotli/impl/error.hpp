//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2024 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#ifndef BOOST_CAPY_BROTLI_IMPL_ERROR_HPP
#define BOOST_CAPY_BROTLI_IMPL_ERROR_HPP

#include <boost/capy/detail/config.hpp>

#include <boost/system/error_category.hpp>
#include <boost/system/is_error_code_enum.hpp>

namespace boost {

namespace system {
template<>
struct is_error_code_enum<
    ::boost::capy::brotli::error>
{
    static bool const value = true;
};
} // system

namespace capy {
namespace brotli {

namespace detail {

struct BOOST_SYMBOL_VISIBLE
    error_cat_type
    : system::error_category
{
    BOOST_CAPY_DECL const char* name(
        ) const noexcept override;
    BOOST_CAPY_DECL bool failed(
        int) const noexcept override;
    BOOST_CAPY_DECL std::string message(
        int) const override;
    BOOST_CAPY_DECL char const* message(
        int, char*, std::size_t
            ) const noexcept override;
    BOOST_SYSTEM_CONSTEXPR error_cat_type()
        : error_category(0xc38951ab8832fb6f)
    {
    }
};

BOOST_CAPY_DECL extern
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

} // brotli
} // capy
} // boost

#endif
