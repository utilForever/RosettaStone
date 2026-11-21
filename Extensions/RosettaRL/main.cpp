// Copyright (c) 2026 Chris Ohk

#include <RosettaRL/NativeTrainer.hpp>

#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace RosettaStone::RL;

#ifdef _WIN32
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
    try
    {
        if (argc > 1)
        {
            TORCH_CHECK(argc >= 4 && std::filesystem::path(argv[1]) == "train",
                        "Usage: RosettaRL train WEIGHTS BATCH [BATCH ...]");

            std::filesystem::path weights(argv[2]);
            PolicyValueNetwork model;

            if (std::filesystem::exists(weights))
            {
                weights = std::filesystem::canonical(weights);
                model->LoadWeights(weights);
            }

            NativeTrainer trainer(model);

            for (int i = 3; i < argc; ++i)
            {
                const std::filesystem::path filename(argv[i]);
                std::ifstream input(filename, std::ios::binary);

                TORCH_CHECK(input.is_open(),
                            "Cannot open training batch: ", filename);

                const auto result = trainer.TrainBatch(input);
                std::cout << "step=" << result.step
                          << " policy_loss=" << result.policyLoss
                          << " value_loss=" << result.valueLoss
                          << " total_loss=" << result.totalLoss << '\n';
            }

            trainer.SaveCheckpoint(weights);
            return EXIT_SUCCESS;
        }

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
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
