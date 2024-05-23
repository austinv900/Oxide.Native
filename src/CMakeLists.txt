cmake_minimum_required(VERSION 3.10)
project(OxideNative)

set(CMAKE_CXX_STANDARD 11)

# Source files
set(SOURCES
    OxideNative.cpp
)

# Add library
add_library(OxideNative SHARED ${SOURCES})

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

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