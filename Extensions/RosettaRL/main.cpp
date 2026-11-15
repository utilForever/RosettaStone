// Copyright (c) 2026 Chris Ohk

#include <torch/types.h>

#include <cstdlib>
#include <exception>
#include <iostream>

int main()
{
    try
    {
        const auto tensor = torch::tensor(
            { 1.0F, 2.0F, 3.0F }, torch::TensorOptions().device(torch::kCPU));
        const auto result = tensor.square().sum().item<float>();

        if (result != 14.0F)
        {
            std::cerr << "LibTorch CPU smoke test failed: expected 14, got "
                      << result << '\n';
            return EXIT_FAILURE;
        }

        std::cout << "LibTorch CPU smoke test passed\n";
        return EXIT_SUCCESS;
    }
    catch (const std::exception& error)
    {
        std::cerr << "LibTorch CPU smoke test failed: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
