# Target name
set(target UnitTests)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Sources
file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build executable
add_executable(${target}
    ${sources})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(${target}
    PRIVATE
    RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../Resources/"
)

# Increase the stack size in MSVC
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
endif ()

# Link libraries
target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    RosettaStone)