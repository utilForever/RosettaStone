# Set URL link
option(TORCH_ENABLE_CUDA "Enable libtorch to use CUDA" OFF)

if(TORCH_ENABLE_CUDA)
    if(NOT DEFINED TORCH_CUDA_VERSION)
        message(FATAL_ERROR "Require variable 'TORCH_CUDA_VERSION'. cu80, cu90 or cu100")
    else()
        set(TORCH_DEVICE ${TORCH_CUDA_VERSION})
    endif()
else()
    set(TORCH_DEVICE cpu)
endif()

set(base_url https://download.pytorch.org/libtorch/${TORCH_DEVICE})

if(APPLE)
    if(NOT TORCH_DEVICE MATCHES "cpu")
        message(FATAL_ERROR "MacOS binaries do not support CUDA.")
    endif()

    set(libtorch_URL ${base_url}/libtorch-macos-latest.zip)

elseif(UNIX)
    if(TORCH_ENABLE_CUDA AND NOT TORCH_DEVICE MATCHES "cu90")
        message(FATAL_ERROR "Linux binaries only support CUDA 9.0 and CPU ver.")
    endif()

    set(libtorch_URL ${base_url}/libtorch-shared-with-deps-latest.zip)

elseif(WIN32)
    set(libtorch_URL ${base_url}/libtorch-win-shared-with-deps-latest.zip)

endif()

# Set download path
set(libtorch_zip ${download_dir}/libtorch_${TORCH_DEVICE}.zip)
set(libtorch_dir ${download_dir}/libtorch_${TORCH_DEVICE})

# Download binaries
if(NOT EXISTS ${libtorch_zip})
    message(STATUS "Download libtorch binaries.")
    file(DOWNLOAD ${libtorch_URL} ${libtorch_zip})
endif()

# Unzip binaries
set(unzip_py ${script_dir}/unzip.py)

if(NOT EXISTS ${libtorch_dir})
    message(STATUS "Unzip libtorch binaries.")
    execute_process(
        COMMAND python ${unzip_py} ${libtorch_zip} ${libtorch_dir}
    )
endif()

# Add package Torch
list(APPEND CMAKE_PREFIX_PATH ${libtorch_dir}/libtorch)

find_package(Torch REQUIRED)
