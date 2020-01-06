#
# Setup Machine Learning library build configuration
#

# Determine the best default option for ML library
if(NOT DEFINED ROSETTARL_ML_LIBRARY)
	find_package(Torch QUIET)
	if(TORCH_FOUND)
	    set(ML_DEFAULT LIBTORCH)
	else()
		set(ML_DEFAULT TINY-DNN)
	endif()
else()
	set(ML_DEFAULT ${ROSETTARL_ML_LIBRARY})
endif()

set(ROSETTARL_ML_LIBRARY ${ML_DEFAULT} CACHE STRING
	"Per-node ML library [TINY-DNN, LIBTORCH]")

set_property(CACHE ROSETTARL_ML_LIBRARY PROPERTY
	STRINGS TINY-DNN LIBTORCH)

# Note - Make the ROSETTARL_ML_LIBRARY build option case-insensitive
string(TOUPPER ${ROSETTARL_ML_LIBRARY} ROSETTARL_ML_LIBRARY_ID)

set(ROSETTARL_ML_LIBRARY_TINY_DNN	FALSE)
set(ROSETTARL_ML_LIBRARY_LIBTORCH	FALSE)

if(${ROSETTARL_ML_LIBRARY_ID} STREQUAL "LIBTORCH")
	set(ROSETTARL_ML_LIBRARY_LIBTORCH TRUE)
else()
	set(ROSETTARL_ML_LIBRARY_TINY_DNN TRUE)
endif()

if(ROSETTARL_ML_LIBRARY_LIBTORCH)
	find_package(Torch REQUIRED)

	get_target_property(TORCH_INCLUDE_PATHS
	                    torch INTERFACE_INCLUDE_DIRECTORIES
	)
	get_target_property(TORCH_LIB_PATH 
	                    torch IMPORTED_LOCATION
	)

	add_definitions(-DROSETTARL_ML_LIBRARY_LIBTORCH)
	include_directories(${TORCH_INCLUDE_PATHS})
	link_libraries(${TORCH_LIB_PATH} ${C10_LIBRARY})
else()
	unset(TORCH_INCLUDE_PATHS	CACHE)
	unset(TORCH_LIB_PATH		CACHE)
	add_definitions(-DROSETTARL_ML_LIBRARY_TINY_DNN)
endif()