#
# Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
# Copyright (c) 2021 Dmitry Arkhipov (grisumbras@gmail.com)
# Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
# Copyright (c) 2025 Mohammad Nejati
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/rts
#

#-------------------------------------------------
#
# Project
#
#-------------------------------------------------
cmake_minimum_required(VERSION 3.8...3.20)
set(BOOST_RTS_VERSION 1)
if (BOOST_SUPERPROJECT_VERSION)
    set(BOOST_RTS_VERSION ${BOOST_SUPERPROJECT_VERSION})
endif ()
project(boost_rts VERSION "${BOOST_RTS_VERSION}" LANGUAGES CXX)
set(BOOST_RTS_IS_ROOT OFF)
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(BOOST_RTS_IS_ROOT ON)
endif ()
set(__ignore__ ${CMAKE_C_COMPILER})

#-------------------------------------------------
#
# Options
#
#-------------------------------------------------
if (BOOST_RTS_IS_ROOT)
    include(CTest)
endif ()
option(BOOST_RTS_BUILD_TESTS "Build boost::rts tests" ${BUILD_TESTING})
option(BOOST_RTS_BUILD_EXAMPLES "Build boost::rts examples" ${BOOST_RTS_IS_ROOT})


# Check if environment variable BOOST_SRC_DIR is set
if (NOT DEFINED BOOST_SRC_DIR AND DEFINED ENV{BOOST_SRC_DIR})
    set(DEFAULT_BOOST_SRC_DIR "$ENV{BOOST_SRC_DIR}")
else ()
    set(DEFAULT_BOOST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif ()
set(BOOST_SRC_DIR ${DEFAULT_BOOST_SRC_DIR} CACHE STRING "Boost source dir to use when running CMake from this directory")

#-------------------------------------------------
#
# Boost modules
#
#-------------------------------------------------
# The boost super-project requires one explicit dependency per-line.
set(BOOST_RTS_DEPENDENCIES
    Boost::config
    Boost::container_hash
    Boost::core
    Boost::mp11
    Boost::system
    Boost::throw_exception
    )

foreach (BOOST_RTS_DEPENDENCY ${BOOST_RTS_DEPENDENCIES})
    if (BOOST_RTS_DEPENDENCY MATCHES "^[ ]*Boost::([A-Za-z0-9_]+)[ ]*$")
        list(APPEND BOOST_RTS_INCLUDE_LIBRARIES ${CMAKE_MATCH_1})
    endif ()
endforeach ()
# Conditional dependencies
if (BOOST_RTS_BUILD_TESTS)
    set(BOOST_RTS_UNIT_TEST_LIBRARIES url)
endif ()
if (BOOST_RTS_BUILD_EXAMPLES)
    # set(BOOST_RTS_EXAMPLE_LIBRARIES url)
endif ()
# Complete dependency list
set(BOOST_INCLUDE_LIBRARIES ${BOOST_RTS_INCLUDE_LIBRARIES} ${BOOST_RTS_UNIT_TEST_LIBRARIES} ${BOOST_RTS_EXAMPLE_LIBRARIES})
set(BOOST_EXCLUDE_LIBRARIES rts)

#-------------------------------------------------
#
# Add Boost Subdirectory
#
#-------------------------------------------------
if (BOOST_RTS_IS_ROOT)
    set(CMAKE_FOLDER Dependencies)
    # Find absolute BOOST_SRC_DIR
    if (NOT IS_ABSOLUTE ${BOOST_SRC_DIR})
        set(BOOST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_SRC_DIR}")
    endif ()

    # Validate BOOST_SRC_DIR
    set(BOOST_SRC_DIR_IS_VALID ON)
    foreach (F "CMakeLists.txt" "Jamroot" "boost-build.jam" "bootstrap.sh" "libs")
        if (NOT EXISTS "${BOOST_SRC_DIR}/${F}")
            message(STATUS "${BOOST_SRC_DIR}/${F} does not exist. Fallback to find_package.")
            set(BOOST_SRC_DIR_IS_VALID OFF)
            break()
        endif ()
    endforeach ()

    # Create Boost interface targets
    if (BOOST_SRC_DIR_IS_VALID)
        # From BOOST_SRC_DIR
        if (BUILD_SHARED_LIBS)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
        endif ()
        set(BOOST_EXCLUDE_LIBRARIES ${PROJECT_NAME})
        set(PREV_BUILD_TESTING ${BUILD_TESTING})
        set(BUILD_TESTING OFF CACHE BOOL "Build the tests." FORCE)
        add_subdirectory(${BOOST_SRC_DIR} Dependencies/boost EXCLUDE_FROM_ALL)
        set(BUILD_TESTING ${PREV_BUILD_TESTING} CACHE BOOL "Build the tests." FORCE)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BOOST_SRC_DIR}/tools/cmake/include")
    else ()
        # From Boost Package
        find_package(Boost REQUIRED COMPONENTS url)
        foreach (BOOST_INCLUDE_LIBRARY ${BOOST_INCLUDE_LIBRARIES})
            if (NOT TARGET Boost::${BOOST_INCLUDE_LIBRARY})
                add_library(Boost::${BOOST_INCLUDE_LIBRARY} ALIAS Boost::headers)
            endif ()
        endforeach ()
    endif ()
    unset(CMAKE_FOLDER)
endif ()

#-------------------------------------------------
#
# Library
#
#-------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE BOOST_RTS_HEADERS CONFIGURE_DEPENDS include/boost/*.hpp include/boost/*.natvis)
file(GLOB_RECURSE BOOST_RTS_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/boost/rts PREFIX "include" FILES ${BOOST_RTS_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${BOOST_RTS_SOURCES})

add_library(boost_rts ${BOOST_RTS_HEADERS} ${BOOST_RTS_SOURCES})
add_library(Boost::rts ALIAS boost_rts)
target_compile_features(boost_rts PUBLIC cxx_constexpr)
target_include_directories(boost_rts PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(boost_rts PUBLIC ${BOOST_RTS_DEPENDENCIES})
target_compile_definitions(boost_rts PUBLIC BOOST_RTS_NO_LIB)
target_compile_definitions(boost_rts PRIVATE BOOST_RTS_SOURCE)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(boost_rts PUBLIC BOOST_RTS_DYN_LINK)
else ()
    target_compile_definitions(boost_rts PUBLIC BOOST_RTS_STATIC_LINK)
endif ()


# Zlib
find_package(ZLIB)
if (ZLIB_FOUND)
    file(GLOB_RECURSE BOOST_RTS_ZLIB_SOURCES CONFIGURE_DEPENDS src_zlib/*.cpp src_zlib/*.hpp)
    file(GLOB_RECURSE BOOST_RTS_ZLIB_HEADERS CONFIGURE_DEPENDS include/boost/rts/zlib/*.hpp)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src_zlib PREFIX "src" FILES ${BOOST_RTS_ZLIB_SOURCES})
    add_library(boost_rts_zlib build/Jamfile ${BOOST_RTS_ZLIB_HEADERS} ${BOOST_RTS_ZLIB_SOURCES})
    add_library(Boost::rts_zlib ALIAS boost_rts_zlib)
    target_link_libraries(boost_rts_zlib PUBLIC boost_rts)
    target_link_libraries(boost_rts_zlib PRIVATE ZLIB::ZLIB)
    target_compile_definitions(boost_rts_zlib PUBLIC BOOST_RTS_HAS_ZLIB)
    target_compile_definitions(boost_rts_zlib PRIVATE BOOST_RTS_SOURCE)
endif ()

#-------------------------------------------------
#
# Tests
#
#-------------------------------------------------
if (BOOST_RTS_BUILD_TESTS)
    add_subdirectory(test)
endif ()

#-------------------------------------------------
#
# Examples
#
#-------------------------------------------------
if (BOOST_RTS_BUILD_EXAMPLES)
    # add_subdirectory(example)
endif ()
