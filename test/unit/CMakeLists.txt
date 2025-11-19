#
# Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/rts
#

add_subdirectory(../../../url/extra/test_suite test_suite)

file(GLOB_RECURSE PFILES CONFIGURE_DEPENDS *.cpp *.hpp)
list(APPEND PFILES
    CMakeLists.txt
    Jamfile)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "" FILES ${PFILES})

add_executable(boost_rts_tests ${PFILES})
target_link_libraries(
    boost_rts_tests PRIVATE
    boost_url_test_suite_with_main
    Boost::rts)

if (TARGET Boost::rts_zlib)
    target_link_libraries(boost_rts_tests PRIVATE Boost::rts_zlib)
endif ()

if (TARGET Boost::rts_brotli)
    target_link_libraries(boost_rts_tests PRIVATE Boost::rts_brotli)
endif ()

# Register individual tests with CTest
boost_url_test_suite_discover_tests(boost_rts_tests)

# Add the main test target to Boost's test suite
add_dependencies(tests boost_rts_tests)
