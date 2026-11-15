find_package(Torch CONFIG QUIET)
if (NOT Torch_FOUND)
    message(FATAL_ERROR
        "BUILD_RL=ON requires LibTorch. Set CMAKE_PREFIX_PATH to the LibTorch "
        "installation, or Torch_DIR to its share/cmake/Torch directory. "
        "Use -DBUILD_RL=OFF to build without LibTorch.")
endif()
