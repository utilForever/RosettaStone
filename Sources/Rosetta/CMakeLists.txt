# Target name
set(target RosettaStone)

# Define
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries
)

# Sources
file(GLOB header_dir
    ${root_dir}/Includes/Rosetta)

file(GLOB_RECURSE headers
    ${header_dir}/*.hpp)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Custom-build event
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(rosettastone_header_gen_py ${root_dir}/Scripts/header_gen.py)
    add_custom_command(
        COMMAND python ${rosettastone_header_gen_py}
        DEPENDS ${headers}
        OUTPUT ${root_dir}/Includes/RosettaStone.hpp
    )
    add_custom_target(rosettastone_header_gen_py ALL
        DEPENDS ${root_dir}/Includes/RosettaStone.hpp)
else ()
    set(rosettastone_header_gen_py ${root_dir}/Scripts/header_gen.py)
    add_custom_command(
        COMMAND python3 ${rosettastone_header_gen_py}
        DEPENDS ${headers}
        OUTPUT ${root_dir}/Includes/RosettaStone.hpp
    )
    add_custom_target(rosettastone_header_gen_py ALL
        DEPENDS ${root_dir}/Includes/RosettaStone.hpp)
endif ()

# Build library
add_library(${target}
    ${sources})
add_dependencies(${target} rosettastone_header_gen_py)

# Project options
set_target_properties(${target}
PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS  true
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
    RESOURCES_DIR="${ROSETTA_ROOT}/Resources/"
)

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)

# Install
install(TARGETS ${target} DESTINATION lib)
install(DIRECTORY ${header_dir} DESTINATION include)
