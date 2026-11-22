# Dependencies
find_package(Torch CONFIG QUIET)

if (NOT Torch_FOUND)
    message(FATAL_ERROR
        "BUILD_RL=ON requires LibTorch. Set CMAKE_PREFIX_PATH to the LibTorch "
        "installation, or Torch_DIR to its share/cmake/Torch directory. "
        "Use -DBUILD_RL=OFF to build without LibTorch.")
endif()

# Python interpreter for CLI tests
if (NOT TARGET Python::Interpreter)
    find_package(Python REQUIRED COMPONENTS Interpreter)
endif()

# LibTorch compile options
separate_arguments(torch_compile_options NATIVE_COMMAND "${TORCH_CXX_FLAGS}")

# RosettaRL model library
add_library(RosettaRLModel STATIC PolicyValueNetwork.cpp NativeTrainer.cpp)

target_include_directories(RosettaRLModel PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Includes")
target_compile_options(RosettaRLModel PUBLIC ${torch_compile_options})
target_link_libraries(RosettaRLModel PUBLIC RosettaStone ${TORCH_LIBRARIES})

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

set(rl_runtime_targets RosettaRL RosettaRLTests)

# Python bindings
if (BUILD_RL_PYTHON)
    # Match PyTorch's pybind11 ABI
    execute_process(
        COMMAND "${Python_EXECUTABLE}" -c [[
import torch

definitions = []
for name in ("COMPILER_TYPE", "STDLIB", "BUILD_ABI"):
    value = getattr(torch._C, f"_PYBIND11_{name}", None)
    if value is not None:
        definitions.append(f'PYBIND11_{name}="{value}"')
print(";".join(definitions))
        ]]
        OUTPUT_VARIABLE torch_python_abi
        OUTPUT_STRIP_TRAILING_WHITESPACE
        COMMAND_ERROR_IS_FATAL ANY
    )

    find_library(TORCH_PYTHON_LIBRARY torch_python
        PATHS "${TORCH_INSTALL_PREFIX}/lib" NO_DEFAULT_PATH REQUIRED)

    pybind11_add_module(pyRosettaRL Python/PolicyValueNetwork.cpp)

    target_include_directories(pyRosettaRL BEFORE PRIVATE "${TORCH_INSTALL_PREFIX}/include")
    target_compile_definitions(pyRosettaRL PRIVATE ${torch_python_abi})
    target_link_libraries(pyRosettaRL PRIVATE RosettaRLModel ${TORCH_PYTHON_LIBRARY})

    file(GENERATE OUTPUT "$<TARGET_FILE_DIR:pyRosettaRL>/rosetta_rl_trainer.py"
        INPUT "${CMAKE_CURRENT_SOURCE_DIR}/Python/rosetta_rl_trainer.py")

    # Native helper for Python weight tests
    add_executable(RosettaRLWeightInterop Tests/WeightArtifactInterop.cpp)
    target_link_libraries(RosettaRLWeightInterop PRIVATE RosettaRLModel)

    add_executable(RosettaRLTrainingReference Tests/TrainingReference.cpp)
    target_link_libraries(RosettaRLTrainingReference PRIVATE RosettaRLModel)

    list(APPEND rl_runtime_targets pyRosettaRL RosettaRLWeightInterop
        RosettaRLTrainingReference)
endif()

# Project options
foreach(target RosettaRLModel ${rl_runtime_targets})
    set_target_properties(${target} PROPERTIES ${DEFAULT_PROJECT_OPTIONS})
    target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_OPTIONS})
endforeach()

# Copy LibTorch DLLs beside runtime targets
if (MSVC)
    file(GLOB torch_dlls "${TORCH_INSTALL_PREFIX}/lib/*.dll")

    if (torch_dlls)
        foreach(target IN LISTS rl_runtime_targets)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${torch_dlls} $<TARGET_FILE_DIR:${target}>
                VERBATIM
            )
        endforeach()
    endif()
endif()

# Register tests
add_test(NAME RosettaRL COMMAND RosettaRL)
add_test(NAME RosettaRLTests COMMAND RosettaRLTests)

# CLI training and checkpoint tests
add_test(NAME RosettaRLTrainCLI
    COMMAND Python::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test_train_cli.py"
        $<TARGET_FILE:RosettaRL> $<TARGET_FILE:RosettaRLTests>
)

if (BUILD_RL_PYTHON)
    # C++/Python weight round-trip
    add_test(NAME RosettaRLWeightInterop
        COMMAND ${CMAKE_COMMAND} -E env
            "PYTHONPATH=$<TARGET_FILE_DIR:pyRosettaRL>"
            "ROSETTA_RL_INTEROP=$<TARGET_FILE:RosettaRLWeightInterop>"
            "${Python_EXECUTABLE}" -m pytest -q
            "${PROJECT_SOURCE_DIR}/Tests/PythonTests/test_rl_weights.py"
    )

    add_test(NAME RosettaRLPythonTrainer
        COMMAND ${CMAKE_COMMAND} -E env
            "PYTHONPATH=$<TARGET_FILE_DIR:pyRosettaRL>"
            "ROSETTA_RL_TESTS=$<TARGET_FILE:RosettaRLTests>"
            "ROSETTA_RL_INTEROP=$<TARGET_FILE:RosettaRLWeightInterop>"
            "${Python_EXECUTABLE}" -m pytest -q
            "${PROJECT_SOURCE_DIR}/Tests/PythonTests/test_rl_trainer.py"
    )
endif()
