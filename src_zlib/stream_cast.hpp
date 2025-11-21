//
// Copyright (c) 2025 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#ifndef SRC_CAPY_ZLIB_STREAM_CAST_HPP
#define SRC_CAPY_ZLIB_STREAM_CAST_HPP

#include <boost/capy/zlib/stream.hpp>

#include <cstddef>

#include <zlib.h>

namespace boost {
namespace capy {
namespace zlib {

//------------------------------------------------

#define SAME_FIELD(T1,T2,M) \
    offsetof(T1,M)==offsetof(T2,M) && \
    sizeof(decltype(T1::M)) == sizeof(decltype(T2::M))

template<class T1, class T2>
constexpr
bool
is_layout_identical()
{
    return
        sizeof(T1) == sizeof(T2) &&
        SAME_FIELD(T1, T2, next_in) &&
        SAME_FIELD(T1, T2, avail_in) &&
        SAME_FIELD(T1, T2, total_in) &&
        SAME_FIELD(T1, T2, next_out) &&
        SAME_FIELD(T1, T2, avail_out) &&
        SAME_FIELD(T1, T2, total_out) &&
        SAME_FIELD(T1, T2, msg) &&
        SAME_FIELD(T1, T2, state) &&
        SAME_FIELD(T1, T2, zalloc) &&
        SAME_FIELD(T1, T2, zfree) &&
        SAME_FIELD(T1, T2, opaque) &&
        SAME_FIELD(T1, T2, data_type) &&
        SAME_FIELD(T1, T2, adler) &&
        SAME_FIELD(T1, T2, reserved)
        ;
}

//------------------------------------------------

template<bool isLayoutIdentical =
    is_layout_identical<stream, z_stream_s>()>
struct stream_cast_impl
{
    explicit
    stream_cast_impl(
        stream& st)
        : pzs_(reinterpret_cast<z_stream_s*>(&st))
        , st_(st)
    {
        zs_.next_in     = st_.next_in;
        zs_.avail_in    = st_.avail_in;
        zs_.total_in    = st_.total_in;
        zs_.next_out    = st_.next_out;
        zs_.avail_out   = st_.avail_out;
        zs_.total_out   = st_.total_out;
        zs_.msg         = nullptr;
        zs_.state       = reinterpret_cast<
            internal_state*>(st_.state);
        zs_.zalloc      = st_.zalloc;
        zs_.zfree       = st_.zfree;
        zs_.opaque      = st_.opaque;
        zs_.data_type   = st_.data_type;
        zs_.adler       = st_.adler;
        zs_.reserved    = st_.reserved;
    }

    ~stream_cast_impl()
    {
        st_.next_in     = zs_.next_in;
        st_.avail_in    = zs_.avail_in;
        st_.total_in    = zs_.total_in;
        st_.next_out    = zs_.next_out;
        st_.avail_out   = zs_.avail_out;
        st_.total_out   = zs_.total_out;
        st_.msg         = zs_.msg;
        st_.state       = zs_.state;
        st_.zalloc      = zs_.zalloc;
        st_.zfree       = zs_.zfree;
        st_.opaque      = zs_.opaque;
        st_.data_type   = zs_.data_type;
        st_.adler       = zs_.adler;
        st_.reserved    = zs_.reserved;
    }

    z_stream_s*
    get() noexcept
    {
        return pzs_;
    }

private:
    z_stream_s* pzs_ = nullptr;
    stream& st_;
    z_stream_s zs_;
};

//------------------------------------------------

template<>
struct stream_cast_impl<true>
{
    explicit
    stream_cast_impl(
        stream& st)
        // VFALCO A pinch of undefined behavior here
        : pzs_(reinterpret_cast<z_stream_s*>(&st))
    {
        
    }

    z_stream_s*
    get() noexcept
    {
        return pzs_;
    }

private:
    z_stream_s* pzs_;
};

//------------------------------------------------

using stream_cast = stream_cast_impl<>;

} // zlib
} // capy
} // boost

#endif
