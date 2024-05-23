cmake_minimum_required(VERSION 3.10)
project(OxideNative)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Include directories
include_directories(${SRC_DIR})

# Source files
set(SOURCES
    ${SRC_DIR}/OxideNative.cpp
)

# Add library
add_library(OxideNative SHARED ${SOURCES})


# Set properties for Windows
if (WIN32)
    set_target_properties(OxideNative PROPERTIES
        OUTPUT_NAME "Oxide.Native"
        PREFIX ""
        SUFFIX ".dll"
    )
endif()

# Set properties for Linux
if (UNIX AND NOT APPLE)
    set_target_properties(OxideNative PROPERTIES
        OUTPUT_NAME "Oxide.Native"
        PREFIX ""
        SUFFIX ".so"
    )
endif()