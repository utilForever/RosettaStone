// Copyright (c) 2026 Chris Ohk

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <c10/core/InferenceMode.h>
#include <torch/serialize.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace RosettaStone::RL
{
namespace
{
static_assert(PlayMode::ObservationSchema::VERSION == 1 &&
              PlayMode::PolicySchema::VERSION == 1 &&
              PolicyValueNetworkImpl::INPUT_SIZE == 444);

const std::pair<const char*, c10::IValue> WEIGHT_METADATA[] = {
    { "format", "RosettaStone.PolicyValueNetwork" },
    { "artifact_version", 1 },
    { "model_version", 1 },
    { "observation_version", PlayMode::ObservationSchema::VERSION },
    { "policy_version", PlayMode::PolicySchema::VERSION }
};

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

void PolicyValueNetworkImpl::SaveWeights(
    const std::filesystem::path& filename) const
{
    torch::serialize::OutputArchive archive;

    for (const auto& [key, value] : WEIGHT_METADATA)
    {
        archive.write(key, value);
    }

    c10::Dict<std::string, torch::Tensor> weights;

    for (const auto& parameter : named_parameters())
    {
        const auto tensor = parameter.value().detach().cpu();

        TORCH_CHECK(torch::isfinite(tensor).all().item<bool>(),
                    "Non-finite weight: ", parameter.key());

        weights.insert(parameter.key(), tensor);
    }

    archive.write("weights", weights);

    // Finalize in memory because LibTorch can abort on a short file write.
    std::ostringstream buffer(std::ios::binary);

    archive.save_to(buffer);

    const auto bytes = buffer.view();
    std::ofstream stream(filename, std::ios::binary);

    TORCH_CHECK(stream.is_open(), "Cannot open weight artifact for writing");

    stream.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    stream.close();

    TORCH_CHECK(stream.good(), "Failed to write weight artifact");
}

void PolicyValueNetworkImpl::LoadWeights(const std::filesystem::path& filename)
{
    std::ifstream stream(filename, std::ios::binary);

    TORCH_CHECK(stream.is_open(), "Cannot open weight artifact for reading");

    torch::serialize::InputArchive archive;
    archive.load_from(stream, torch::kCPU);

    for (const auto& [key, expected] : WEIGHT_METADATA)
    {
        c10::IValue actual;

        TORCH_CHECK(
            archive.try_read(key, actual) &&
                actual.tagKind() == expected.tagKind() && actual == expected,
            "Incompatible weight artifact ", key, ": expected ", expected);
    }

    c10::IValue payload;

    TORCH_CHECK(archive.try_read("weights", payload) && payload.isGenericDict(),
                "Weight artifact requires a weights dictionary");

    const auto weights = payload.toGenericDict();
    const auto parameters = named_parameters();

    TORCH_CHECK(weights.size() == parameters.size(),
                "Weight artifact parameter count mismatch");

    std::vector<torch::Tensor> staged;
    staged.reserve(parameters.size());

    for (const auto& parameter : parameters)
    {
        const auto entry = weights.find(parameter.key());

        TORCH_CHECK(entry != weights.end() && entry->value().isTensor(),
                    "Missing or invalid weight: ", parameter.key());

        const auto tensor = entry->value().toTensor();
        const auto& destination = parameter.value();

        TORCH_CHECK(tensor.sizes() == destination.sizes(),
                    "Weight shape mismatch: ", parameter.key(), "; expected ",
                    destination.sizes(), ", got ", tensor.sizes());
        TORCH_CHECK(tensor.layout() == torch::kStrided &&
                        tensor.scalar_type() == destination.scalar_type(),
                    "Weight dtype/layout mismatch: ", parameter.key());
        TORCH_CHECK(torch::isfinite(tensor).all().item<bool>(),
                    "Non-finite weight: ", parameter.key());

        // Preserve parameter inference state regardless of the caller's mode.
        const c10::InferenceMode mode(destination.is_inference());
        staged.push_back(
            tensor.detach().to(destination.options(), false, true));
    }

    // Finish validation and device allocations before replacing live storage.
    for (std::size_t i = 0; i < parameters.size(); ++i)
    {
        parameters[i].value().set_data(staged[i]);
    }
}
}  // namespace RosettaStone::RL
