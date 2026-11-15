find_package(Torch CONFIG QUIET)
if (NOT Torch_FOUND)
    message(FATAL_ERROR
        "BUILD_RL=ON requires LibTorch. Set CMAKE_PREFIX_PATH to the LibTorch "
        "installation, or Torch_DIR to its share/cmake/Torch directory. "
        "Use -DBUILD_RL=OFF to build without LibTorch.")
endif()

set(target RosettaRL)
add_executable(${target} main.cpp)

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

separate_arguments(torch_compile_options NATIVE_COMMAND "${TORCH_CXX_FLAGS}")

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
    ${torch_compile_options}
)
target_link_libraries(${target}
    PRIVATE
    RosettaStone
    ${TORCH_LIBRARIES}
)

if (MSVC)
    file(GLOB torch_dlls "${TORCH_INSTALL_PREFIX}/lib/*.dll")

    if (torch_dlls)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${torch_dlls} $<TARGET_FILE_DIR:${target}>
            VERBATIM
        )
    endif()
endif()

add_test(NAME RosettaRL COMMAND RosettaRL)
