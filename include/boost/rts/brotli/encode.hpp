//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_BROTLI_ENCODE_HPP
#define BOOST_RTS_BROTLI_ENCODE_HPP

#include <boost/rts/brotli/shared_dictionary.hpp>

#include <cstdint>

namespace boost {
namespace rts {
namespace brotli {

/** Opaque structure that holds encoder state. */
struct encoder_state;

/** Opaque type for pointer to different possible internal
    structures containing dictionary prepared for the encoder
*/
struct encoder_prepared_dictionary;

/** Options for ::BROTLI_PARAM_MODE parameter. */
enum class encoder_mode
{
    generic = 0,
    text    = 1,
    font    = 2
};

/** Operations that can be performed by streaming encoder. */
enum class encoder_operation
{
    process       = 0,
    flush         = 1,
    finish        = 2,
    emit_metadata = 3
};

/** Options to be used with ::SetParameter. */
enum class encoder_parameter
{
    mode                             = 0,
    quality                          = 1,
    lgwin                            = 2,
    lgblock                          = 3,
    disable_literal_context_modeling = 4,
    size_hint                        = 5,
    large_window                     = 6,
    npostfix                         = 7,
    ndirect                          = 8,
    stream_offset                    = 9
};

/** Different constants in Brotli API */
enum constants
{
    min_window_bits = 10,
    max_window_bits = 24,

    large_max_window_bits = 30,

    min_input_block_bits = 16,
    max_input_block_bits = 24,

    min_quality = 0,
    max_quality = 11,

    default_quality = 11,
    default_window  = 22,
    default_mode    = 0
};

/** Provides the Brotli compression API */
struct BOOST_SYMBOL_VISIBLE
    encode_service
{
    virtual bool
    set_parameter(
        encoder_state* state,
        encoder_parameter param,
        std::uint32_t value) const noexcept = 0;

    virtual encoder_state*
    create_instance(
        alloc_func alloc_func,
        free_func free_func,
        void* opaque) const noexcept = 0;

    virtual void
    destroy_instance(encoder_state* state) const noexcept = 0;

    virtual std::size_t
    max_compressed_size(std::size_t input_size) const noexcept = 0;

    virtual bool
    compress(
        int quality,
        int lgwin,
        encoder_mode mode,
        std::size_t input_size,
        const std::uint8_t input_buffer[],
        std::size_t* encoded_size,
        std::uint8_t encoded_buffer[]) const noexcept = 0;

    virtual bool
    compress_stream(
        encoder_state* state,
        encoder_operation op,
        std::size_t* available_in,
        const std::uint8_t** next_in,
        std::size_t* available_out,
        std::uint8_t** next_out,
        std::size_t* total_out) const noexcept = 0;

    virtual bool
    is_finished(encoder_state* state) const noexcept = 0;

    virtual bool
    has_more_output(encoder_state* state) const noexcept = 0;

    virtual const std::uint8_t*
    take_output(
        encoder_state* state,
        std::size_t* size) const noexcept = 0;

    virtual std::uint32_t
    version() const noexcept = 0;

#if 0
    virtual encoder_prepared_dictionary*
    prepare_dictionary(
        shared_dictionary_type type,
        std::size_t data_size,
        const std::uint8_t data[],
        int quality,
        alloc_func alloc_func,
        free_func free_func,
        void* opaque) const noexcept = 0;

    virtual void
    destroy_prepared_dictionary(
        encoder_prepared_dictionary* dictionary) const noexcept = 0;

    virtual bool
    attach_prepared_dictionary(
        encoder_state* state,
        const encoder_prepared_dictionary* dictionary) const noexcept = 0;

    virtual std::size_t
    estimate_peak_memory_usage(
        int quality,
        int lgwin,
        std::size_t input_size) const noexcept = 0;

    virtual std::size_t
    get_prepared_dictionary_size(
        const encoder_prepared_dictionary* dictionary) const noexcept = 0;
#endif
};

BOOST_RTS_DECL
encode_service&
install_encode_service(polystore& ctx);

} // brotli
} // rts
} // boost

#endif
