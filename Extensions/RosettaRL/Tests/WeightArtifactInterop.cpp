// Copyright (c) 2026 Chris Ohk

#include <torch/serialize.h>
#include <torch/utils.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

using namespace RosettaStone::RL;

// Used by pytest to exercise artifact exchange with a separate native process.
int main(int argc, char** argv)
{
    try
    {
        TORCH_CHECK(
            argc == 4 && (std::string(argv[1]) == "save" ||
                          std::string(argv[1]) == "check"),
            "Usage: RosettaRLWeightInterop save|check weights reference");

        torch::manual_seed(1073);

        torch::NoGradGuard guard;
        PolicyValueNetwork model;

        if (std::string(argv[1]) == "save")
        {
            auto batch =
                torch::arange(2 * PolicyValueNetworkImpl::INPUT_SIZE,
                              torch::kInt32)
                    .reshape({ 2, PolicyValueNetworkImpl::INPUT_SIZE });
            batch.select(1, 0).fill_(1);

            const auto [logits, values] = model->forward(batch);
            model->SaveWeights(argv[2]);

            torch::serialize::OutputArchive reference;
            reference.write("observations", batch, true);
            reference.write("logits", logits, true);
            reference.write("values", values, true);
            reference.save_to(argv[3]);
        }
        else
        {
            model->LoadWeights(argv[2]);

            torch::serialize::InputArchive reference;
            reference.load_from(argv[3], torch::kCPU);

            torch::Tensor batch, logits, values;
            reference.read("observations", batch, true);
            reference.read("logits", logits, true);
            reference.read("values", values, true);

            const auto actual = model->forward(batch);

            TORCH_CHECK(torch::allclose(actual.first, logits, 1e-5, 1e-6),
                        "Cross-runtime policy output mismatch");
            TORCH_CHECK(torch::allclose(actual.second, values, 1e-5, 1e-6),
                        "Cross-runtime value output mismatch");
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
