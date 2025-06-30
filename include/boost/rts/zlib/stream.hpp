//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_ZLIB_STREAM_HPP
#define BOOST_RTS_ZLIB_STREAM_HPP

namespace boost {
namespace rts {
namespace zlib {

struct stream
{
    using alloc_func = void*(*)(void*, unsigned int, unsigned int);
    using free_func = void(*)(void*, void*);

    unsigned char* next_in;   // next input byte
    unsigned int   avail_in;  // number of bytes available at next_in
    unsigned long  total_in;  // total number of input bytes read so far

    unsigned char* next_out;  // next output byte will go here
    unsigned int   avail_out; // remaining free space at next_out
    unsigned long  total_out; // total number of bytes output so far

    char*          msg;       // last error message, NULL if no error
    void*          state;     // not visible by applications

    alloc_func     zalloc;    // used to allocate internal state
    free_func      zfree;     // used to deallocate internal state
    void*          opaque;    // private data object passed to zalloc and zfree

    int            data_type; // best guess about the data type: binary or text
                              // for deflate, or the decoding state for inflate
    unsigned long  adler;     // Adler-32 or CRC-32 value of the uncompressed data
    unsigned long  reserved;  // reserved for future use
};

} // zlib
} // rts
} // boost

#endif
