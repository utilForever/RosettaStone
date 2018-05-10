# Target name
set(target HSppGUI)

find_package(OpenGL REQUIRED)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
else()
	find_package(glfw3 REQUIRED)
endif()

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Libraries/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/imgui)

link_directories(${CMAKE_SOURCE_DIR}/Libraries/glfw/lib)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	link_libraries(OpenGL32)
	link_libraries(glfw3)
else()
	link_libraries(OpenGL)
	link_libraries(glfw)
endif()

# Sources
file(GLOB sources
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build executable
add_executable(${target}
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
target_compile_definitions(${target}
	PRIVATE
	RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../Resources/"
)

# Link libraries
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_link_libraries(${target}
		PRIVATE
		${DEFAULT_LINKER_OPTIONS}
		Hearthstonepp
		imgui
		winix)
else()
	target_link_libraries(${target}
		PRIVATE
		${DEFAULT_LINKER_OPTIONS}
		Hearthstonepp
		imgui)
endif()