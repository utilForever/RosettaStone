
# Define common variables for RosettaRL and its sub-projects
set(root_dir        ${PROJECT_SOURCE_DIR})
set(script_dir      ${CMAKE_CURRENT_SOURCE_DIR}/Scripts)
set(external_dir    ${CMAKE_CURRENT_SOURCE_DIR}/External)
set(download_dir    ${external_dir}/Downloads)

# Download + find_package(Torch)
include(${external_dir}/libtorch.cmake)
get_target_property(TORCH_INCLUDE_PATHS
                    torch INTERFACE_INCLUDE_DIRECTORIES
)
get_target_property(TORCH_LIB_PATH 
                    torch IMPORTED_LOCATION
)
# let's be verbose. this part can be a problem again
message(STATUS "using PyTorch: torch(CMake Target)")
foreach(include_dir ${TORCH_INCLUDE_PATHS})
    message(STATUS "  - include : ${include_dir}")
endforeach()
message(STATUS "  - libpath : ${TORCH_LIB_PATH}")
message(STATUS "  - c10     : ${C10_LIBRARY}")

# Sources
file(GLOB_RECURSE headers
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.hpp)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# Build library
add_library(RosettaRL
    ${sources}
)

# Project options
set_target_properties(RosettaRL
PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS  true
    ${DEFAULT_PROJECT_OPTIONS}
)

# Includes
target_include_directories(RosettaRL
PUBLIC
    ${root_dir}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${TORCH_INCLUDE_PATHS}
)

# Compile options
target_compile_options(RosettaRL
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

# Compile definitions
target_compile_definitions(RosettaRL
PUBLIC
    RESOURCES_DIR="${root_dir}/Resources/"
)

# Link libraries
target_link_libraries(RosettaRL
PUBLIC
    RosettaStone
    ${DEFAULT_LINKER_OPTIONS}
    ${TORCH_LIB_PATH} ${C10_LIBRARY} # ${TORCH_LIBRARIES}
    caffe2::mkl protobuf::libprotobuf Threads::Threads   
)

add_subdirectory(Tests/AlphaZeroTests)
add_subdirectory(Tests/MCTSTests)

# Install
install(TARGETS ${target} DESTINATION lib)
install(DIRECTORY ${header_dir} DESTINATION include)
