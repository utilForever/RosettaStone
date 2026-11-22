// Copyright (c) 2026 Chris Ohk

#include <RosettaRL/NativeTrainer.hpp>

#include <torch/serialize.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace RosettaStone::RL
{
namespace
{
void CheckTarget(const torch::Tensor& target, const torch::Tensor& prediction,
                 const char* name)
{
    TORCH_CHECK(target.defined() && target.sizes() == prediction.sizes(), name,
                " must have shape ", prediction.sizes());
    TORCH_CHECK(target.layout() == torch::kStrided &&
                    target.scalar_type() == prediction.scalar_type() &&
                    target.device() == prediction.device(),
                name,
                " must be a dense tensor with the model's dtype and device");
}
}  // namespace

NativeTrainer::NativeTrainer(PolicyValueNetwork model)
    : m_model(std::move(model)), m_optimizer(m_model->parameters(), 0.01)
{
    // Do nothing
}

std::array<torch::Tensor, 3> ComputeTrainingLosses(
    const PolicyValueNetworkImpl& model,
    const std::pair<torch::Tensor, torch::Tensor>& predictions,
    const torch::Tensor& policyTargets, const torch::Tensor& outcomes)
{
    const auto& [logits, values] = predictions;

    TORCH_CHECK(values.numel() > 0, "Training requires a nonempty batch");
    CheckTarget(policyTargets, logits, "Policy targets");
    CheckTarget(outcomes, values, "Outcomes");
    TORCH_CHECK(
        policyTargets.ge(0).all().item<bool>() &&
            (policyTargets.sum(1) - 1).abs().le(1e-5).all().item<bool>(),
        "Policy targets must be finite, nonnegative and sum to one per row");
    TORCH_CHECK(
        outcomes.eq(0).logical_or(outcomes.abs().eq(1)).all().item<bool>(),
        "Outcomes must be -1 (loss), 0 (draw) or +1 (win)");

    const auto policyLoss =
        -(policyTargets.detach() * logits.log_softmax(1)).sum(1).mean();
    const auto valueLoss = (values - outcomes.detach()).square().mean();
    auto totalLoss = policyLoss + valueLoss;

    for (const auto& parameter : model.parameters())
    {
        totalLoss = totalLoss + 1e-4 * parameter.square().sum();
    }

    TORCH_CHECK(std::isfinite(totalLoss.item<double>()),
                "Non-finite training loss");

    return { policyLoss, valueLoss, totalLoss };
}

TrainingStep NativeTrainer::TrainBatch(const torch::Tensor& observations,
                                       const torch::Tensor& policyTargets,
                                       const torch::Tensor& outcomes)
{
    m_model->train();

    const auto [policyLoss, valueLoss, totalLoss] = ComputeTrainingLosses(
        *m_model, m_model->forward(observations), policyTargets, outcomes);
    const TrainingStep result{ m_steps + 1, policyLoss.item<double>(),
                               valueLoss.item<double>(),
                               totalLoss.item<double>() };

    m_optimizer.zero_grad();
    totalLoss.backward();
    m_optimizer.step();

    m_steps = result.step;
    return result;
}

std::vector<torch::Tensor> ReadTrainingBatch(std::istream& input)
{
    std::vector<torch::Tensor> batch;

    torch::load(batch, input, torch::kCPU);

    TORCH_CHECK(
        batch.size() == 3,
        "Expected observations, policy targets and outcomes in training batch");

    return batch;
}

TrainingStep NativeTrainer::TrainBatch(std::istream& input)
{
    const auto batch = ReadTrainingBatch(input);
    return TrainBatch(batch[0], batch[1], batch[2]);
}

void SaveTrainingCheckpoint(const PolicyValueNetworkImpl& model,
                            const std::filesystem::path& weights)
{
    auto target = weights;

    while (std::filesystem::is_symlink(target))
    {
        if (std::filesystem::exists(target))
        {
            target = std::filesystem::canonical(target);
            break;
        }

        // A link may name the file that the first checkpoint will create.
        target = target.parent_path() / std::filesystem::read_symlink(target);
    }

    const auto temporary =
        target.parent_path() /
        (".rosetta-weights-" +
         std::to_string(
             std::chrono::steady_clock::now().time_since_epoch().count()) +
         ".tmp");

    TORCH_CHECK(std::ofstream(temporary, std::ios::noreplace).is_open(),
                "Cannot create temporary checkpoint");

    try
    {
        const auto destination = std::filesystem::status(target);

        if (std::filesystem::exists(destination))
        {
            std::filesystem::permissions(temporary, destination.permissions());
        }

        model.SaveWeights(temporary);
        std::filesystem::rename(temporary, target);
    }
    catch (...)
    {
        std::error_code error;
        std::filesystem::remove(temporary, error);
        throw;
    }
}

void NativeTrainer::SaveCheckpoint(const std::filesystem::path& weights) const
{
    SaveTrainingCheckpoint(*m_model, weights);
}
}  // namespace RosettaStone::RL
