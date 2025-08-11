#
# Copyright (c) 2025 Mohammad Nejati
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/rts
#

# Provides imported targets:
#   Libpsl::Libpsl

find_path(Libpsl_INCLUDE_DIR NAMES libpsl.h)
find_library(Libpsl_LIBRARY NAMES psl libpsl)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libpsl
    REQUIRED_VARS
    Libpsl_INCLUDE_DIR
    Libpsl_LIBRARY
)

if(Libpsl_FOUND)
    add_library(Libpsl::Libpsl UNKNOWN IMPORTED)
    set_target_properties(Libpsl::Libpsl PROPERTIES
        IMPORTED_LOCATION "${Libpsl_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Libpsl_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(
    Libpsl_INCLUDE_DIR
    Libpsl_LIBRARY)
