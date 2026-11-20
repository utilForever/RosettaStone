find_package(Torch CONFIG QUIET)

if (NOT Torch_FOUND)
    message(FATAL_ERROR
        "BUILD_RL=ON requires LibTorch. Set CMAKE_PREFIX_PATH to the LibTorch "
        "installation, or Torch_DIR to its share/cmake/Torch directory. "
        "Use -DBUILD_RL=OFF to build without LibTorch.")
endif()

separate_arguments(torch_compile_options NATIVE_COMMAND "${TORCH_CXX_FLAGS}")

# RosettaRL model library
add_library(RosettaRLModel STATIC PolicyValueNetwork.cpp NativeTrainer.cpp)
target_include_directories(RosettaRLModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_options(RosettaRLModel PUBLIC ${torch_compile_options})
target_link_libraries(RosettaRLModel
    PUBLIC
    RosettaStone
    ${TORCH_LIBRARIES}
)

# RosettaRL executable
add_executable(RosettaRL main.cpp)
target_link_libraries(RosettaRL PRIVATE RosettaRLModel)

# Use wmain for Unicode paths
if (MINGW)
    target_link_options(RosettaRL PRIVATE -municode)
endif()

# RosettaRL tests
add_executable(RosettaRLTests
    Tests/NativeTrainerTests.cpp
    Tests/PolicyValueNetworkTests.cpp
    Tests/WeightArtifactTests.cpp
)
target_link_libraries(RosettaRLTests PRIVATE RosettaRLModel doctest::doctest)

foreach(target RosettaRLModel RosettaRL RosettaRLTests)
    set_target_properties(${target} PROPERTIES ${DEFAULT_PROJECT_OPTIONS})
    target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_OPTIONS})
endforeach()

if (MSVC)
    file(GLOB torch_dlls "${TORCH_INSTALL_PREFIX}/lib/*.dll")

    if (torch_dlls)
        foreach(target RosettaRL RosettaRLTests)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${torch_dlls} $<TARGET_FILE_DIR:${target}>
                VERBATIM
            )
        endforeach()
    endif()
endif()

add_test(NAME RosettaRL COMMAND RosettaRL)
add_test(NAME RosettaRLTests COMMAND RosettaRLTests)

if (BUILD_RL_PYTHON)
    execute_process(
        COMMAND ${Python_EXECUTABLE} -c
            "import torch; print(';'.join('PYBIND11_' + name + '=\"' + getattr(torch._C, '_PYBIND11_' + name) + '\"' for name in ('COMPILER_TYPE', 'STDLIB', 'BUILD_ABI') if getattr(torch._C, '_PYBIND11_' + name) is not None))"
        OUTPUT_VARIABLE torch_python_abi
        OUTPUT_STRIP_TRAILING_WHITESPACE
        COMMAND_ERROR_IS_FATAL ANY
    )
    find_library(TORCH_PYTHON_LIBRARY torch_python
        PATHS "${TORCH_INSTALL_PREFIX}/lib" NO_DEFAULT_PATH REQUIRED)

    pybind11_add_module(pyRosettaRL Python/PolicyValueNetwork.cpp)
    # Match the pybind11 internals used by the selected PyTorch installation.
    target_include_directories(pyRosettaRL BEFORE PRIVATE "${TORCH_INSTALL_PREFIX}/include")
    target_compile_definitions(pyRosettaRL PRIVATE ${torch_python_abi})
    target_link_libraries(pyRosettaRL PRIVATE RosettaRLModel ${TORCH_PYTHON_LIBRARY})

    add_executable(RosettaRLWeightInterop Tests/WeightArtifactInterop.cpp)
    target_link_libraries(RosettaRLWeightInterop PRIVATE RosettaRLModel)

    foreach(target pyRosettaRL RosettaRLWeightInterop)
        set_target_properties(${target} PROPERTIES ${DEFAULT_PROJECT_OPTIONS})
        target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_OPTIONS})

        if (MSVC AND torch_dlls)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${torch_dlls} $<TARGET_FILE_DIR:${target}>
                VERBATIM
            )
        endif()
    endforeach()

    add_test(NAME RosettaRLWeightInterop
        COMMAND ${CMAKE_COMMAND} -E env
            "PYTHONPATH=$<TARGET_FILE_DIR:pyRosettaRL>"
            "ROSETTA_RL_INTEROP=$<TARGET_FILE:RosettaRLWeightInterop>"
            ${Python_EXECUTABLE} -m pytest -q
            ${PROJECT_SOURCE_DIR}/Tests/PythonTests/test_rl_weights.py
    )
endif()
