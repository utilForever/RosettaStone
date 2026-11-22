// Copyright (c) 2026 Chris Ohk

#include <ATen/Parallel.h>
#include <torch/serialize.h>
#include <torch/utils.h>

#include <RosettaRL/NativeTrainer.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

#include "ReplayTrainingBatch.hpp"

using namespace RosettaStone::RL;

namespace
{
c10::Dict<std::string, torch::Tensor> SnapshotWeights(
    const PolicyValueNetwork& model)
{
    c10::Dict<std::string, torch::Tensor> weights;

    for (const auto& parameter : model->named_parameters())
    {
        // Later optimizer steps must not change the reference snapshots.
        weights.insert(parameter.key(), parameter.value().detach().clone());
    }

    return weights;
}

torch::Tensor Losses(const TrainingStep& step)
{
    return torch::tensor({ step.policyLoss, step.valueLoss, step.totalLoss },
                         torch::kFloat64);
}
}  // namespace

// Pytest compares these native snapshots with the actual Python trainer.
int main(int argc, char** argv)
{
    try
    {
        TORCH_CHECK(argc == 2,
                    "Usage: RosettaRLTrainingReference reference.pt");

        at::set_num_threads(1);
        at::set_num_interop_threads(1);

        const auto [observations, policy, outcomes] =
            Tests::ReplayTrainingBatch();

        torch::manual_seed(1074);

        PolicyValueNetwork model;
        model->eval();

        torch::serialize::OutputArchive reference;
        reference.write("observations", observations, true);
        reference.write("policy", policy, true);
        reference.write("outcomes", outcomes, true);
        reference.write("initial_weights", SnapshotWeights(model));

        {
            torch::NoGradGuard guard;
            const auto [logits, values] = model->forward(observations);

            reference.write("logits", logits, true);
            reference.write("values", values, true);
        }

        NativeTrainer trainer(model);
        auto step = trainer.TrainBatch(observations, policy, outcomes);

        reference.write("first_losses", Losses(step), true);

        c10::Dict<std::string, torch::Tensor> gradients;

        for (const auto& parameter : model->named_parameters())
        {
            TORCH_CHECK(parameter.value().grad().defined(),
                        "Missing native gradient: ", parameter.key());
            gradients.insert(parameter.key(),
                             parameter.value().grad().detach().clone());
        }

        reference.write("gradients", gradients);
        reference.write("step_weights", SnapshotWeights(model));

        for (std::size_t i = 1; i < 64; ++i)
        {
            step = trainer.TrainBatch(observations, policy, outcomes);
        }

        reference.write("last_losses", Losses(step), true);

        torch::NoGradGuard guard;
        const auto [logits, values] = model->forward(observations);

        reference.write("final_logits", logits, true);
        reference.write("final_values", values, true);
        reference.save_to(argv[1]);

        return EXIT_SUCCESS;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
