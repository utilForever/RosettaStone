find_package(Torch CONFIG QUIET)

if (NOT Torch_FOUND)
    message(FATAL_ERROR
        "BUILD_RL=ON requires LibTorch. Set CMAKE_PREFIX_PATH to the LibTorch "
        "installation, or Torch_DIR to its share/cmake/Torch directory. "
        "Use -DBUILD_RL=OFF to build without LibTorch.")
endif()

separate_arguments(torch_compile_options NATIVE_COMMAND "${TORCH_CXX_FLAGS}")

# RosettaRL model library
add_library(RosettaRLModel STATIC PolicyValueNetwork.cpp)
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

# RosettaRL tests
add_executable(RosettaRLTests
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
