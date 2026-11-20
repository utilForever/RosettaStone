// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_RL_NATIVE_TRAINER_HPP
#define ROSETTASTONE_RL_NATIVE_TRAINER_HPP

#include <torch/optim/sgd.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <cstddef>
#include <iosfwd>

namespace RosettaStone::RL
{
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

 private:
    PolicyValueNetwork m_model;
    torch::optim::SGD m_optimizer;
    std::size_t m_steps = 0;
};
}  // namespace RosettaStone::RL

#endif  // ROSETTASTONE_RL_NATIVE_TRAINER_HPP
