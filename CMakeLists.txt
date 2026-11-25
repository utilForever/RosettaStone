# CMake version
cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Builds/CMake")

# Declare project
project(RosettaStone)

# Set RosettaStone's root directory
if (NOT ROSETTA_ROOT)
	set(ROSETTA_ROOT ${PROJECT_SOURCE_DIR})
endif()

# Enable testing
enable_testing()

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Includes
include_directories(Includes)
include_directories(Extensions/RosettaPython/Includes)

# Dependencies
find_package(doctest CONFIG REQUIRED)
find_package(effolkronium_random CONFIG REQUIRED)
find_package(lyra CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

option(BUILD_RL_PYTHON "Build optional Python bindings for the shared RL model" OFF)

if (BUILD_FROM_PIP OR BUILD_RL_PYTHON)
    # vcpkg's Python wrapper can select headers from a different interpreter.
    if (COMMAND _find_package)
        _find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
    else()
        find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
    endif()
endif()

find_package(pybind11 CONFIG REQUIRED)

# Compile options
include(Builds/CMake/CompileOptions.cmake)

# Build type - Release by default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Overrides
set(CMAKE_MACOSX_RPATH ON)

# Set resources
set(RESOURCES_DIR ${ROSETTA_ROOT}/Resources)
set(RESOURCES_JSONS
    ${RESOURCES_DIR}/cards.collectible.json
    ${RESOURCES_DIR}/cards.json)

# Project modules
option(BUILD_RL "Build optional LibTorch reinforcement-learning targets" OFF)

if (BUILD_RL_PYTHON AND NOT BUILD_RL)
    message(FATAL_ERROR "BUILD_RL_PYTHON=ON requires BUILD_RL=ON")
endif()

add_subdirectory(Sources/Rosetta)
add_subdirectory(Tests/UnitTests)
add_subdirectory(Extensions/RosettaConsole)
add_subdirectory(Extensions/RosettaTool)

if (BUILD_RL)
    add_subdirectory(Extensions/RosettaRL)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Builds/setup.py.in ${CMAKE_CURRENT_SOURCE_DIR}/setup.py)

# Code coverage - Debug only
# NOTE: Code coverage results with an optimized (non-Debug) build may be misleading
option(BUILD_COVERAGE "Build code coverage" OFF)
if (CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage UnitTests coverage)
endif()

if (BUILD_FROM_PIP)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
add_subdirectory(Extensions/RosettaPython)

# The sample codec and its rounding test change the floating-point environment.
set_property(SOURCE
    Sources/Rosetta/PlayMode/Agents/SelfPlaySample.cpp
    Tests/UnitTests/PlayMode/Games/SchemaGoldenTests.cpp
    TARGET_DIRECTORY RosettaStone UnitTests
    APPEND PROPERTY COMPILE_OPTIONS
    "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-frounding-math>"
    "$<$<CXX_COMPILER_ID:MSVC>:/fp:strict>")
