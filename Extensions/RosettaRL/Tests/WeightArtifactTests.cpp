// Copyright (c) 2026 Chris Ohk

#define DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES
#include <doctest/doctest.h>

#include <c10/core/InferenceMode.h>
#include <torch/cuda.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <chrono>
#include <filesystem>

using namespace RosettaStone::RL;

namespace
{
struct TemporaryArtifact
{
    std::filesystem::path path =
        std::filesystem::temp_directory_path() /
        ("rosetta-weights-" +
         std::to_string(
             std::chrono::steady_clock::now().time_since_epoch().count()) +
         ".pt");

    ~TemporaryArtifact()
    {
        std::error_code error;
        std::filesystem::remove(path, error);
    }
};
}  // namespace

DOCTEST_TEST_CASE("[WeightArtifact] - RoundTripPreservesOutputsAndModelState")
{
    TemporaryArtifact file;

    auto batch =
        torch::arange(2 * PolicyValueNetworkImpl::INPUT_SIZE, torch::kInt32)
            .reshape({ 2, PolicyValueNetworkImpl::INPUT_SIZE });
    batch.select(1, 0).fill_(1);

    for (const auto dtype :
         { torch::kFloat32, torch::kFloat64, torch::kFloat16 })
    {
        PolicyValueNetwork source;
        source->to(dtype);
        source->SaveWeights(file.path);

        PolicyValueNetwork target;
        target->to(dtype);
        target->eval();

        const auto handle = target->parameters().front();

        target->LoadWeights(file.path);

        DOCTEST_CHECK_FALSE(target->is_training());
        DOCTEST_CHECK(handle.is_same(target->parameters().front()));

        const auto expected = source->forward(batch);
        const auto actual = target->forward(batch);

        DOCTEST_CHECK(torch::equal(expected.first, actual.first));
        DOCTEST_CHECK(torch::equal(expected.second, actual.second));

        if (torch::cuda::is_available())
        {
            target->to(torch::kCUDA);
            target->LoadWeights(file.path);

            DOCTEST_CHECK(target->parameters().front().is_cuda());

            target->SaveWeights(file.path);
            source->LoadWeights(file.path);

            DOCTEST_CHECK(torch::equal(source->parameters().front(),
                                       target->parameters().front().cpu()));
        }
    }
}

DOCTEST_TEST_CASE("[WeightArtifact] - UnicodePathRoundTrip")
{
    TemporaryArtifact file;
    file.path += std::filesystem::path(u8"_\uAC00\uC911\uCE58.pt");

    PolicyValueNetwork source;
    source->SaveWeights(file.path);

    DOCTEST_REQUIRE(std::filesystem::exists(file.path));

    PolicyValueNetwork target;
    target->LoadWeights(file.path);

    const auto expected = source->parameters();
    const auto actual = target->parameters();

    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        DOCTEST_CHECK(torch::equal(expected[i], actual[i]));
    }
}

DOCTEST_TEST_CASE("[WeightArtifact] - InferenceModeLoadPreservesTraining")
{
    TemporaryArtifact file;

    PolicyValueNetwork source;
    source->SaveWeights(file.path);

    PolicyValueNetwork target;
    {
        const c10::InferenceMode mode;
        target->LoadWeights(file.path);

        DOCTEST_CHECK(c10::InferenceMode::is_enabled());
    }

    const auto batch =
        torch::ones({ 2, PolicyValueNetworkImpl::INPUT_SIZE }, torch::kInt32);
    const auto [logits, values] = target->forward(batch);

    (logits.square().mean() + values.square().mean()).backward();

    for (const auto& parameter : target->parameters())
    {
        DOCTEST_CHECK_FALSE(parameter.is_inference());
        DOCTEST_CHECK(parameter.requires_grad());
        DOCTEST_REQUIRE(parameter.grad().defined());
        DOCTEST_CHECK(torch::isfinite(parameter.grad()).all().item<bool>());
    }
}
