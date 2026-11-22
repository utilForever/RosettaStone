// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_RL_NATIVE_TRAINER_HPP
#define ROSETTASTONE_RL_NATIVE_TRAINER_HPP

#include <torch/optim/sgd.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <array>
#include <cstddef>
#include <filesystem>
#include <iosfwd>
#include <utility>
#include <vector>

namespace RosettaStone::RL
{
//! Policy, value and regularized total losses on the forward pass's graph.
std::array<torch::Tensor, 3> ComputeTrainingLosses(
    const PolicyValueNetworkImpl& model,
    const std::pair<torch::Tensor, torch::Tensor>& predictions,
    const torch::Tensor& policyTargets, const torch::Tensor& outcomes);

//! Reads the native CPU archive in observation, policy target, outcome order.
std::vector<torch::Tensor> ReadTrainingBatch(std::istream& input);

//! Atomically replaces the shared weights at the checkpoint's target.
void SaveTrainingCheckpoint(const PolicyValueNetworkImpl& model,
                            const std::filesystem::path& weights);

struct TrainingStep
{
    std::size_t step;
    double policyLoss;
    double valueLoss;
    double totalLoss;
};

//! Plain SGD on the shared model. The model handle retains the trained weights.
class NativeTrainer
{
 public:
    explicit NativeTrainer(PolicyValueNetwork model);

    //! Trains on one nonempty batch of raw observations, normalized visit
    //! probabilities [B, NUM_ACTIONS] and player-relative outcomes [B].
    //! Outcomes are -1 for a loss, 0 for a draw and +1 for a win.
    //! Both targets use the model's floating dtype and device.
    //! Returns pre-update losses and the number of successful steps this run.
    TrainingStep TrainBatch(const torch::Tensor& observations,
                            const torch::Tensor& policyTargets,
                            const torch::Tensor& outcomes);

    //! Reads one CPU batch saved with torch::save(vector<Tensor>, stream).
    TrainingStep TrainBatch(std::istream& input);

    //! Follows symlinks and atomically replaces the checkpoint at the target.
    void SaveCheckpoint(const std::filesystem::path& weights) const;

 private:
    PolicyValueNetwork m_model;
    torch::optim::SGD m_optimizer;
    std::size_t m_steps = 0;
};
}  // namespace RosettaStone::RL

#endif  // ROSETTASTONE_RL_NATIVE_TRAINER_HPP
