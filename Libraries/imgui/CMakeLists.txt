# Target name
set(target imgui)

# Includes
include_directories(${CMAKE_SOURCE_DIR}/Libraries/SFML/include)

# Sources
file(GLOB headers
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build library
add_library(${target}
    ${sources})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

# Compile options
target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)