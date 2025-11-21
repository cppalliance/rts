//
// Copyright (c) 2024 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#include <boost/capy/zlib/error.hpp>

namespace boost {
namespace capy {
namespace zlib {
namespace detail {

const char*
error_cat_type::
name() const noexcept
{
    return "boost.capy.zlib";
}

bool
error_cat_type::
failed(int ev) const noexcept
{
    return ev < 0;
}

std::string
error_cat_type::
message(int ev) const
{
    return message(ev, nullptr, 0);
}

char const*
error_cat_type::
message(
    int ev,
    char*,
    std::size_t) const noexcept
{
    switch(static_cast<error>(ev))
    {
    case error::ok: return "Z_OK";
    case error::stream_end: return "Z_STREAM_END";
    case error::need_dict: return "Z_NEED_DICT";
    case error::errno_: return "Z_ERRNO";
    case error::stream_err: return "Z_STREAM_ERROR";
    case error::data_err: return "Z_DATA_ERROR";
    case error::mem_err: return "Z_MEM_ERROR";
    case error::buf_err: return "Z_BUF_ERROR";
    case error::version_err: return "Z_VERSION_ERROR";
    default:
        return "unknown";
    }
}

// msvc 14.0 has a bug that warns about inability
// to use constexpr construction here, even though
// there's no constexpr construction
#if defined(_MSC_VER) && _MSC_VER <= 1900
# pragma warning( push )
# pragma warning( disable : 4592 )
#endif

#if defined(__cpp_constinit) && __cpp_constinit >= 201907L
constinit error_cat_type error_cat;
#else
error_cat_type error_cat;
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1900
# pragma warning( pop )
#endif

} // detail
} // zlib
} // capy
} // boost
