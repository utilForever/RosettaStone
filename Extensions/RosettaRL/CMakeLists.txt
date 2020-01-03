# Target name
set(target RosettaRL)

# Add prefix path to identify Libtorch
list(APPEND CMAKE_PREFIX_PATH "C:/Libtorch")

# Machine Learning library options
include(CMake/MLLibraryOptions.cmake)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Includes)

# Sources
file(GLOB_RECURSE headers
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.hpp)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# Build library
add_library(${target}
    ${sources}
)

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

# Compile options
target_compile_options(${target}
    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

# Compile definitions
target_compile_definitions(${target}
PUBLIC
    RESOURCES_DIR="${root_dir}/Resources/"
)

# Link libraries
target_link_libraries(${target}
    PUBLIC
    RosettaStone
    ${DEFAULT_LINKER_OPTIONS}
)

add_subdirectory(Tests/AlphaZeroTests)
add_subdirectory(Tests/MCTSTests)

# Install
install(TARGETS ${target} DESTINATION lib)
install(DIRECTORY ${header_dir} DESTINATION include)
