//
// Copyright (c) 2024 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/brotli/error.hpp>

namespace boost {
namespace rts {
namespace brotli {
namespace detail {

const char*
error_cat_type::
name() const noexcept
{
    return "boost.rts.brotli";
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

    case error::no_error: return "no_error";
    case error::success: return "success";
    case error::needs_more_input: return "needs_more_input";
    case error::needs_more_output: return "needs_more_output";
    case error::format_exuberant_nibble: return "format_exuberant_nibble";
    case error::format_reserved: return "format_reserved";
    case error::format_exuberant_meta_nibbl: return "format_exuberant_meta_nibbl";
    case error::format_simple_huffman_alphabet: return "format_simple_huffman_alphabet";
    case error::format_simple_huffman_same: return "format_simple_huffman_same";
    case error::format_cl_space: return "format_cl_space";
    case error::format_huffman_space: return "format_huffman_space";
    case error::format_context_map_repea: return "format_context_map_repea";
    case error::format_block_length_1: return "format_block_length_1";
    case error::format_block_length_2: return "format_block_length_2";
    case error::format_transform: return "format_transform";
    case error::format_dictionary: return "format_dictionary";
    case error::format_window_bits: return "format_window_bits";
    case error::format_padding_1: return "format_padding_1";
    case error::format_padding_2: return "format_padding_2";
    case error::format_distance: return "format_distance";
    case error::compound_dictionary: return "compound_dictionary";
    case error::dictionary_not_set: return "dictionary_not_set";
    case error::invalid_arguments: return "invalid_arguments";
    case error::alloc_context_modes: return "alloc_context_modes";
    case error::alloc_tree_groups: return "alloc_tree_groups";
    case error::alloc_context_map: return "alloc_context_map";
    case error::alloc_ring_buffer_1: return "alloc_ring_buffer_1";
    case error::alloc_ring_buffer_2: return "alloc_ring_buffer_2";
    case error::alloc_block_type_trees: return "alloc_block_type_trees";
    case error::unreachable: return "unreachable";
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
} // brotli
} // rts
} // boost
