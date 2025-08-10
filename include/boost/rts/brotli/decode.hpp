//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_BROTLI_DECODE_HPP
#define BOOST_RTS_BROTLI_DECODE_HPP

#include <boost/rts/brotli/error.hpp>
#include <boost/rts/brotli/shared_dictionary.hpp>

#include <cstdint>

namespace boost {
namespace rts {
namespace brotli {

/** Opaque structure that holds decoder state. */
struct decoder_state;

/** Result type for decompress and decompress_stream functions. */
enum class decoder_result
{
    error = 0,
    success = 1,
    needs_more_input = 2,
    needs_more_output = 3
};

/** Options to be used with set_parameter. */
enum class decoder_param
{
    disable_ring_buffer_reallocation = 0,
    large_window = 1
};

/** Callback to fire on metadata block start. */
using metadata_start_func = void (*)(void* opaque, std::size_t size);

/** Callback to fire on metadata block chunk becomes available. */
using metadata_chunk_func = void (*)(void* opaque, const std::uint8_t* data, std::size_t size);

/** Provides the Brotli decompression API */
struct BOOST_SYMBOL_VISIBLE
decode_service
    : public service
{
    virtual bool
    set_parameter(
        decoder_state* state,
        decoder_param param,
        std::uint32_t value) const noexcept = 0;

    virtual decoder_state*
    create_instance(
        alloc_func alloc_func,
        free_func free_func,
        void* opaque) const noexcept = 0;

    virtual void
    destroy_instance(decoder_state* state) const noexcept = 0;

    virtual decoder_result
    decompress(
        std::size_t encoded_size,
        const std::uint8_t encoded_buffer[],
        std::size_t* decoded_size,
        std::uint8_t decoded_buffer[]) const noexcept = 0;

    virtual decoder_result
    decompress_stream(
        decoder_state* state,
        std::size_t* available_in,
        const std::uint8_t** next_in,
        std::size_t* available_out,
        std::uint8_t** next_out,
        std::size_t* total_out) const noexcept = 0;

    virtual bool
    has_more_output(const decoder_state* state) const noexcept = 0;

    virtual const std::uint8_t*
    take_output(decoder_state* state, std::size_t* size) const noexcept = 0;

    virtual bool
    is_used(const decoder_state* state) const noexcept = 0;

    virtual bool
    is_finished(const decoder_state* state) const noexcept = 0;

    virtual error
    get_error_code(const decoder_state* state) const noexcept = 0;

    virtual const char*
    error_string(error c) const noexcept = 0;

    virtual std::uint32_t
    version() const noexcept = 0;

#if 0
    virtual bool
    attach_dictionary(
        decoder_state* state,
        shared_dictionary_type type,
        std::size_t data_size,
        const std::uint8_t data[]) const noexcept = 0;

    virtual void
    set_metadata_callbacks(
        decoder_state* state,
        metadata_start_func start_func,
        metadata_chunk_func chunk_func,
        void* opaque) const noexcept = 0;
#endif
};

BOOST_RTS_DECL
decode_service&
install_decode_service(context& ctx);

} // brotli
} // rts
} // boost

#endif
