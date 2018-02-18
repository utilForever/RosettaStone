# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Builds/CMake")

# Declare project
project(Hearthstonepp)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Includes
include_directories(Includes)
include_directories(Libraries)
include_directories(Libraries/glfw/include)
include_directories(LIbraries/imgui)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    include_directories(Libraries/winix)
endif()

# Compile options
include(Builds/CMake/CompileOptions.cmake)

# Build type - Release by default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Overrides
set(CMAKE_MACOSX_RPATH ON)

# Set resources
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(RESOURCES_JSONS
    ${RESOURCES_DIR}/cards.collectible.json
    ${RESOURCES_DIR}/cards.json)

# Project modules
add_subdirectory(Sources)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_subdirectory(Libraries/winix)
endif()
add_subdirectory(Libraries/glfw)
add_subdirectory(Programs/Console)
add_subdirectory(Programs/GUI)

if (BUILD_FROM_PIP)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()