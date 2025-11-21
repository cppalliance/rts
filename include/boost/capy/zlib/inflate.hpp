//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/capy
//

#ifndef BOOST_CAPY_ZLIB_INFLATE_HPP
#define BOOST_CAPY_ZLIB_INFLATE_HPP

#include <boost/capy/polystore_fwd.hpp>
#include <boost/capy/detail/config.hpp>
#include <boost/capy/zlib/stream.hpp>

namespace boost {
namespace capy {
namespace zlib {

/** Provides the ZLib decompression API
*/
struct BOOST_SYMBOL_VISIBLE
    inflate_service
{
    virtual char const* version() const noexcept = 0;
    virtual int init(stream& st) const = 0;
    virtual int init2(stream& st, int windowBits) const = 0;
    virtual int inflate(stream& st, int flush) const = 0;
    virtual int inflate_end(stream& st) const = 0;
    virtual int set_dict(stream& st, unsigned char const* dict, unsigned len) const = 0;
    virtual int get_dict(stream& st, unsigned char* dest, unsigned* len) const = 0;
    virtual int sync(stream& st) const = 0;
    virtual int dup(stream& dest, stream& src) const = 0;
    virtual int reset(stream& st) const = 0;
    virtual int reset2(stream& st, int windowBits) const = 0;
    virtual int prime(stream& st, int bits, int value) const = 0;
    virtual long mark(stream& st) const = 0;
    virtual int get_header(stream& st, void* header) const = 0;
    virtual int back_init(stream& st, int windowBits, unsigned char* window) const = 0;
    virtual int back_end(stream& st) const = 0;
    virtual unsigned long compile_flags() const = 0;
};

BOOST_CAPY_DECL
inflate_service&
install_inflate_service(polystore& ctx);

} // zlib
} // capy
} // boost

#endif
