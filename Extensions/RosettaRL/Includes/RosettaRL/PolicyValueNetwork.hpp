// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_RL_POLICY_VALUE_NETWORK_HPP
#define ROSETTASTONE_RL_POLICY_VALUE_NETWORK_HPP

#include <torch/nn/module.h>
#include <torch/nn/modules/linear.h>

#include <Rosetta/PlayMode/Games/Observation.hpp>

#include <filesystem>
#include <span>
#include <utility>

namespace RosettaStone::RL
{
//! Copies observation v1 scalars in member/row-major order, including version.
//! Returns an owning CPU int32 tensor [B, 444]; an empty batch is supported.
//! Throws std::invalid_argument for an unsupported observation version.
torch::Tensor EncodeObservationBatch(
    std::span<const PlayMode::Observation> observations);

//! Fixed MVP network: signed log1p inputs, Linear(444, 128), ReLU, two heads.
//! All layers are registered for normal LibTorch training, to(), and archives.
class PolicyValueNetworkImpl : public torch::nn::Module
{
 public:
    static constexpr std::int64_t INPUT_SIZE =
        PlayMode::ObservationSchema::FLAT_SIZE;

    PolicyValueNetworkImpl();

    //! Accepts raw int32 [B, INPUT_SIZE] on the same device as the model.
    //! Returns unmasked logits [B, PolicySchema::NUM_ACTIONS] and values [B]
    //! in [-1, 1] for ObservationSchema::SELF (+1 win, 0 draw, -1 loss).
    //! Output dtype follows the parameters (float32 by default).
    //! Invalid shape, dtype, version, or device throws c10::Error.
    std::pair<torch::Tensor, torch::Tensor> forward(
        const torch::Tensor& observations);

    //! Versioned, weights-only artifact shared by C++ and Python.
    //! Stores CPU tensors in their original dtype; loading preserves the
    //! destination device/dtype/inference state and requires matching dtypes.
    //! Invalid or incomplete artifacts throw before changing any parameter.
    void SaveWeights(const std::filesystem::path& filename) const;
    void LoadWeights(const std::filesystem::path& filename);

 private:
    torch::nn::Linear m_shared{ nullptr };
    torch::nn::Linear m_policy{ nullptr };
    torch::nn::Linear m_value{ nullptr };
};

TORCH_MODULE(PolicyValueNetwork);
}  // namespace RosettaStone::RL

#endif  // ROSETTASTONE_RL_POLICY_VALUE_NETWORK_HPP
