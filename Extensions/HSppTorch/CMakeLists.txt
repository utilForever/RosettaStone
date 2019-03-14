# Target name
set(target HSppTorch)

# Defines
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Includes
include_directories(
    ${root_dir}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes)

# Sources
file(GLOB header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/hspp_torch)

file(GLOB_RECURSE headers
    ${header_dir}/Includes/*.hpp)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# Build library
add_library(${target}
    ${sources})

# Project Options
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
target_compile_definitions(${target}
    PRIVATE
    RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../Resources/"
)

# Link libraries
target_link_libraries(${target}
        PRIVATE
        ${DEFAULT_LINKER_OPTIONS}
        Hearthstonepp)

# Install
install(TARGETS ${target} DESTINATION lib)
install(DIRECTORY ${header_dir} DESTINATION include)
