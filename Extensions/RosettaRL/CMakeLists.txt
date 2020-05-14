# Target name
set(target RosettaRL)

# Add prefix path to identify Libtorch
# list(APPEND CMAKE_PREFIX_PATH "C:/Libtorch")

# Machine Learning library options
include(CMake/MLLibraryOptions.cmake)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Includes)

# Sources
file(GLOB_RECURSE headers
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/Agents/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/AlphaZero/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/Judges/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/MCTS/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/FieldEnums.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/GameDataBridge.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/IInputGetter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/NeuralNetwork.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/NeuralNetworkInput.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/NeuralNetworkOutput.hpp)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Agents/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/AlphaZero/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Judges/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/MCTS/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/GameDataBridge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/NeuralNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/NeuralNetworkInput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/NeuralNetworkOutput.cpp)

if(${ROSETTARL_ML_LIBRARY_ID} STREQUAL "LIBTORCH")
    set(headers ${headers}
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/libtorch/CNNModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/libtorch/InputDataConverter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/libtorch/NeuralNetworkImpl.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/libtorch/NeuralNetworkInputImpl.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/libtorch/NeuralNetworkOutputImpl.hpp)

    set(sources ${sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/libtorch/CNNModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/libtorch/InputDataConverter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/libtorch/NeuralNetworkImpl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/libtorch/NeuralNetworkInputImpl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/libtorch/NeuralNetworkOutputImpl.cpp)
else()
    set(headers ${headers}
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/tiny-dnn/InputDataConverter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/tiny-dnn/NeuralNetworkImpl.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/tiny-dnn/NeuralNetworkInputImpl.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/NeuralNet/tiny-dnn/NeuralNetworkOutputImpl.hpp)

    set(sources ${sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/tiny-dnn/InputDataConverter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/tiny-dnn/NeuralNetworkImpl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/tiny-dnn/NeuralNetworkInputImpl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/NeuralNet/tiny-dnn/NeuralNetworkOutputImpl.cpp)
endif()

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
add_subdirectory(Trains/Programs/GenerateTrainData)
add_subdirectory(Trains/Programs/Train)

# Install
install(TARGETS ${target} DESTINATION lib)
install(DIRECTORY ${header_dir} DESTINATION include)
