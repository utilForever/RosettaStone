# Target name
set(target pyRosetta)

# Define
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Sources
file(GLOB_RECURSE sources
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add Pybind11 module
pybind11_add_module(${target} ${sources})

# Project options
set_target_properties(${target}
		PROPERTIES
		${DEFAULT_PROJECT_OPTIONS})

# Link libraries
target_link_libraries(${target}
		PRIVATE
		${DEFAULT_LINKER_OPTIONS}
		RosettaStone)