// Copyright (c) 2026 Chris Ohk

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <stdexcept>

namespace RosettaStone::RL
{
namespace
{
static_assert(PlayMode::ObservationSchema::VERSION == 1 &&
              PlayMode::PolicySchema::VERSION == 1 &&
              PolicyValueNetworkImpl::INPUT_SIZE == 444);

void Flatten(std::int32_t*& destination, std::int32_t value)
{
    *destination++ = value;
}

template <typename T, std::size_t N>
void Flatten(std::int32_t*& destination, const std::array<T, N>& values)
{
    for (const auto& value : values)
    {
        Flatten(destination, value);
    }
}
}  // namespace

torch::Tensor EncodeObservationBatch(
    std::span<const PlayMode::Observation> observations)
{
    auto batch = torch::empty(
        { static_cast<std::int64_t>(observations.size()),
          PolicyValueNetworkImpl::INPUT_SIZE },
        torch::TensorOptions().dtype(torch::kInt32).device(torch::kCPU));
    auto* destination = batch.data_ptr<std::int32_t>();

    for (const auto& observation : observations)
    {
        const auto& [version, turn, players, heroes, heroPowers, weapons, board,
                     hand, secrets, chooseOne, choices] = observation;

        if (version != PlayMode::ObservationSchema::VERSION)
        {
            throw std::invalid_argument("Invalid network observation version");
        }

        Flatten(destination, version);
        Flatten(destination, turn);
        Flatten(destination, players);
        Flatten(destination, heroes);
        Flatten(destination, heroPowers);
        Flatten(destination, weapons);
        Flatten(destination, board);
        Flatten(destination, hand);
        Flatten(destination, secrets);
        Flatten(destination, chooseOne);
        Flatten(destination, choices);
    }

    return batch;
}

PolicyValueNetworkImpl::PolicyValueNetworkImpl()
    : m_shared(register_module("shared", torch::nn::Linear(INPUT_SIZE, 128))),
      m_policy(register_module(
          "policy",
          torch::nn::Linear(128, PlayMode::PolicySchema::NUM_ACTIONS))),
      m_value(register_module("value", torch::nn::Linear(128, 1)))
{
    // Do not reseed here: callers control initialization with manual_seed().
}

std::pair<torch::Tensor, torch::Tensor> PolicyValueNetworkImpl::forward(
    const torch::Tensor& observations)
{
    TORCH_CHECK(observations.defined() && observations.dim() == 2 &&
                    observations.size(1) == INPUT_SIZE,
                "PolicyValueNetwork expects observations shaped [B, ",
                INPUT_SIZE, "]");
    TORCH_CHECK(observations.scalar_type() == torch::kInt32,
                "PolicyValueNetwork expects raw int32 observations");
    TORCH_CHECK(
        observations.device() == m_shared->weight.device(),
        "PolicyValueNetwork observations and model must share a device");
    TORCH_CHECK(observations.select(1, 0)
                    .eq(PlayMode::ObservationSchema::VERSION)
                    .all()
                    .item<bool>(),
                "Invalid network observation version");

    auto features = observations.to(torch::kFloat32);
    // Keep large card IDs and flags from saturating the value head.
    // IDs/flags stay scalar; revisit for broader card pools.
    features = features.sign() * features.abs().log1p();
    features = features.to(m_shared->weight.scalar_type());

    const auto hidden = torch::relu(m_shared->forward(features));

    return { m_policy->forward(hidden),
             torch::tanh(m_value->forward(hidden)).squeeze(-1) };
}
}  // namespace RosettaStone::RL
