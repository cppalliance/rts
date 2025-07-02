#
# Copyright (c) 2025 Mohammad Nejati
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/rts
#

# Provides imported targets:
#   Brotli::common
#   Brotli::decoder
#   Brotli::encoder

find_path(Brotli_INCLUDE_DIR "brotli/decode.h")
find_library(Brotli_COMMON_LIBRARY NAMES "brotlicommon")
find_library(Brotli_DEC_LIBRARY NAMES "brotlidec")
find_library(Brotli_ENC_LIBRARY NAMES "brotlienc")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Brotli
    REQUIRED_VARS
        Brotli_INCLUDE_DIR
        Brotli_COMMON_LIBRARY
        Brotli_DEC_LIBRARY
        Brotli_ENC_LIBRARY
)

if(Brotli_FOUND)
    add_library(Brotli::common UNKNOWN IMPORTED)
    set_target_properties(Brotli::common PROPERTIES
        IMPORTED_LOCATION ${Brotli_COMMON_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${Brotli_INCLUDE_DIR})

    add_library(Brotli::decoder UNKNOWN IMPORTED)
    set_target_properties(Brotli::decoder PROPERTIES
        IMPORTED_LOCATION ${Brotli_DEC_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${Brotli_INCLUDE_DIR})

    add_library(Brotli::encoder UNKNOWN IMPORTED)
    set_target_properties(Brotli::encoder PROPERTIES
        IMPORTED_LOCATION ${Brotli_ENC_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${Brotli_INCLUDE_DIR})
endif()

mark_as_advanced(
    Brotli_INCLUDE_DIR
    Brotli_COMMON_LIBRARY
    Brotli_DEC_LIBRARY
    Brotli_ENC_LIBRARY)
