# Target name
set(target MCTSTests)

# Sources
file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Build executable
add_executable(${target}
    ${sources}
)   

# Project options
set_target_properties(${target}
PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

# Includes
target_include_directories(${target}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compile options
# GCC and Clang compiler options
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        # /wd4996       # -> disable warning: non-Standard std::tr1 namespace and TR1-only machinery (because of gtest)		
        -Wno-unused-variable
    )
endif()

# Link libraries
target_link_libraries(${target}
PRIVATE
	RosettaRL
)
