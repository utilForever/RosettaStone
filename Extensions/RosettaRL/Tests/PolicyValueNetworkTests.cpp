// Copyright (c) 2026 Chris Ohk

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// LibTorch also defines CHECK macros.
#define DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES
#include <doctest/doctest.h>

#include <torch/cuda.h>
#include <torch/optim/sgd.h>
#include <torch/serialize.h>
#include <torch/utils.h>

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <limits>
#include <sstream>

using namespace RosettaStone;
using namespace PlayMode;
using namespace RL;

namespace
{
torch::Tensor InputBatch()
{
    std::array<Observation, 2> observations;
    observations[0].turn = { 6, ObservationSchema::MAIN_ACTION };
    observations[0].players[0] = { 3, 1, 0, 0, 0, 1, 20, 0, 0, 1, 0 };
    observations[0].heroes[0] = { 1, 637, 0, 0, 30, 30, 0, 0, 0, 0, 0 };
    observations[0].hand[0] = { 1, 1174, 6, 6, 7, 7, 0, 0, 0, 0, 0 };
    observations[1] = observations[0];
    observations[1].turn[ObservationSchema::TURN_NUMBER] = 12;
    observations[1].heroes[0][ObservationSchema::HEALTH] = 15;
    observations[1].hand[0][ObservationSchema::COST] = 4;

    return EncodeObservationBatch(observations);
}
}  // namespace

DOCTEST_TEST_CASE("[PolicyValueNetwork] - ObservationLayoutAndOwnership")
{
    std::array<Observation, 2> observations;

    auto& first = observations[0];
    first.turn = { 7, ObservationSchema::MAIN_ACTION };
    first.players[0][0] = 3;
    first.players[1][10] = 4;
    first.heroes[0][0] = 5;
    first.heroes[1][10] = 6;
    first.heroPowers[0][0] = 7;
    first.heroPowers[1][10] = 8;
    first.weapons[0][0] = 9;
    first.weapons[1][10] = 10;
    first.board[0][0][0] = 11;
    first.board[0][6][10] = 12;
    first.board[1][0][0] = 13;
    first.board[1][6][10] = 14;
    first.hand[0][0] = 15;
    first.hand[9][10] = 16;
    first.secrets = { 17, 18, 19, 20, 21 };
    first.chooseOne[0][0] = 22;
    first.chooseOne[9][3] = 23;
    first.choices[0][0] = 24;
    first.choices[3][10] = -25;

    observations[1].turn[0] = std::numeric_limits<std::int32_t>::min();

    const auto batch = EncodeObservationBatch(observations);

    DOCTEST_CHECK(batch.device().is_cpu());
    DOCTEST_CHECK((batch.scalar_type() == torch::kInt32));
    DOCTEST_REQUIRE(batch.sizes() == torch::IntArrayRef({ 2, 444 }));

    auto expected = torch::zeros({ 2, 444 }, torch::kInt32);
    const std::array<std::pair<int, int>, 26> entries{
        { { 0, 1 },    { 1, 7 },    { 2, 1 },    { 3, 3 },    { 24, 4 },
          { 25, 5 },   { 46, 6 },   { 47, 7 },   { 68, 8 },   { 69, 9 },
          { 90, 10 },  { 91, 11 },  { 167, 12 }, { 168, 13 }, { 244, 14 },
          { 245, 15 }, { 354, 16 }, { 355, 17 }, { 356, 18 }, { 357, 19 },
          { 358, 20 }, { 359, 21 }, { 360, 22 }, { 399, 23 }, { 400, 24 },
          { 443, -25 } }
    };

    for (const auto& [column, value] : entries)
    {
        expected[0][column] = value;
    }

    expected[1][0] = 1;
    expected[1][1] = std::numeric_limits<std::int32_t>::min();

    DOCTEST_CHECK(torch::equal(batch, expected));

    first.turn[0] = 99;

    DOCTEST_CHECK_EQ(batch[0][1].item<int>(), 7);
    DOCTEST_CHECK(EncodeObservationBatch({}).sizes() ==
                  torch::IntArrayRef({ 0, 444 }));

    ++observations[1].schemaVersion;

    DOCTEST_CHECK_THROWS_AS(EncodeObservationBatch(observations),
                            std::invalid_argument);
}

DOCTEST_TEST_CASE(
    "[PolicyValueNetwork] - ForwardShapeRangeAndBatchIndependence")
{
    torch::manual_seed(1072);

    PolicyValueNetwork network;
    const auto batch = InputBatch();
    const auto [logits, values] = network->forward(batch);

    DOCTEST_CHECK(logits.sizes() ==
                  torch::IntArrayRef({ 2, static_cast<std::int64_t>(
                                              PolicySchema::NUM_ACTIONS) }));
    DOCTEST_CHECK(values.sizes() == torch::IntArrayRef({ 2 }));
    DOCTEST_CHECK((logits.scalar_type() == torch::kFloat32));
    DOCTEST_CHECK((values.scalar_type() == torch::kFloat32));
    DOCTEST_CHECK(torch::isfinite(logits).all().item<bool>());
    DOCTEST_CHECK(torch::isfinite(values).all().item<bool>());
    DOCTEST_CHECK(values.ge(-1).logical_and(values.le(1)).all().item<bool>());

    for (std::int64_t row = 0; row < batch.size(0); ++row)
    {
        const auto [singleLogits, singleValue] =
            network->forward(batch.narrow(0, row, 1));

        DOCTEST_CHECK(
            torch::allclose(logits[row], singleLogits[0], 1e-5, 1e-6));
        DOCTEST_CHECK(torch::allclose(values[row], singleValue[0], 1e-5, 1e-6));
    }

    const auto [emptyLogits, emptyValues] =
        network->forward(EncodeObservationBatch({}));

    DOCTEST_CHECK(emptyLogits.sizes() == torch::IntArrayRef({ 0, 4846 }));
    DOCTEST_CHECK(emptyValues.sizes() == torch::IntArrayRef({ 0 }));

    auto extremes = batch.clone();
    extremes[0].fill_(std::numeric_limits<std::int32_t>::min());
    extremes[1].fill_(std::numeric_limits<std::int32_t>::max());
    extremes.select(1, 0).fill_(ObservationSchema::VERSION);

    for (const auto dtype : { torch::kFloat32, torch::kFloat16 })
    {
        DOCTEST_INFO("dtype: ", dtype);

        network->to(dtype);

        const auto [extremeLogits, extremeValues] = network->forward(extremes);

        DOCTEST_CHECK((extremeLogits.scalar_type() == dtype));
        DOCTEST_CHECK((extremeValues.scalar_type() == dtype));
        DOCTEST_CHECK(torch::isfinite(extremeLogits).all().item<bool>());
        DOCTEST_CHECK(torch::isfinite(extremeValues).all().item<bool>());
        DOCTEST_CHECK(extremeValues.abs().le(1).all().item<bool>());
    }
}

DOCTEST_TEST_CASE("[PolicyValueNetwork] - RejectsInvalidTensorContracts")
{
    PolicyValueNetwork network;
    auto batch = InputBatch();

    DOCTEST_CHECK_THROWS_AS(network->forward({}), c10::Error);
    DOCTEST_CHECK_THROWS_AS(network->forward(batch[0]), c10::Error);
    DOCTEST_CHECK_THROWS_AS(network->forward(batch.unsqueeze(0)), c10::Error);
    DOCTEST_CHECK_THROWS_AS(network->forward(batch.narrow(1, 0, 443)),
                            c10::Error);
    DOCTEST_CHECK_THROWS_AS(network->forward(batch.to(torch::kFloat32)),
                            c10::Error);
    DOCTEST_CHECK_THROWS_AS(network->forward(batch.to(torch::kInt64)),
                            c10::Error);

    batch[1][0] = ObservationSchema::VERSION + 1;

    DOCTEST_CHECK_THROWS_AS(network->forward(batch), c10::Error);
}

DOCTEST_TEST_CASE(
    "[PolicyValueNetwork] - GradientsReachAllRegisteredParameters")
{
    torch::manual_seed(1072);

    PolicyValueNetwork network;
    const auto parameters = network->named_parameters();

    DOCTEST_REQUIRE_EQ(network->named_children().size(), 3);
    DOCTEST_REQUIRE_EQ(parameters.size(), 6);

    torch::optim::SGD optimizer(network->parameters(), 0.01);

    const auto [logits, values] = network->forward(InputBatch());
    const auto loss = logits.square().mean() + (values - 0.5).square().mean();

    loss.backward();

    for (const auto& parameter : parameters)
    {
        DOCTEST_INFO(parameter.key());
        DOCTEST_CHECK(parameter.value().requires_grad());

        const auto gradient = parameter.value().grad();

        DOCTEST_REQUIRE(gradient.defined());
        DOCTEST_CHECK(gradient.sizes() == parameter.value().sizes());
        DOCTEST_CHECK(torch::isfinite(gradient).all().item<bool>());
        DOCTEST_CHECK_GT(gradient.abs().sum().item<float>(), 0.0f);
    }

    const auto before = parameters["shared.weight"].detach().clone();

    optimizer.step();

    DOCTEST_CHECK_FALSE(torch::equal(before, parameters["shared.weight"]));
}

DOCTEST_TEST_CASE(
    "[PolicyValueNetwork] - FixedSeedReproducesCPUParametersAndOutputs")
{
    torch::manual_seed(1072);
    PolicyValueNetwork first;

    torch::manual_seed(1072);
    PolicyValueNetwork second;

    const auto firstParameters = first->named_parameters();
    const auto secondParameters = second->named_parameters();

    DOCTEST_REQUIRE_EQ(firstParameters.size(), secondParameters.size());

    for (const auto& parameter : firstParameters)
    {
        DOCTEST_CHECK(
            torch::equal(parameter.value(), secondParameters[parameter.key()]));
    }

    const auto batch = InputBatch();
    const auto [firstLogits, firstValues] = first->forward(batch);
    const auto [secondLogits, secondValues] = second->forward(batch);

    DOCTEST_CHECK(torch::equal(firstLogits, secondLogits));
    DOCTEST_CHECK(torch::equal(firstValues, secondValues));

    torch::manual_seed(1073);
    PolicyValueNetwork third;

    DOCTEST_CHECK_FALSE(
        torch::equal(firstParameters["shared.weight"],
                     third->named_parameters()["shared.weight"]));
}

DOCTEST_TEST_CASE("[PolicyValueNetwork] - NativeArchivePreservesOutputs")
{
    PolicyValueNetwork network;
    std::stringstream weights;

    torch::save(network, weights);

    PolicyValueNetwork restored;

    torch::load(restored, weights);

    const auto batch = InputBatch();
    const auto [logits, values] = network->forward(batch);
    const auto [restoredLogits, restoredValues] = restored->forward(batch);

    DOCTEST_CHECK(torch::equal(logits, restoredLogits));
    DOCTEST_CHECK(torch::equal(values, restoredValues));
}

DOCTEST_TEST_CASE("[PolicyValueNetwork] - DeviceAndDtypeMoves")
{
    PolicyValueNetwork network;
    const auto batch = InputBatch();

    network->to(torch::kFloat64);

    const auto [doubleLogits, doubleValues] = network->forward(batch);

    DOCTEST_CHECK((doubleLogits.scalar_type() == torch::kFloat64));
    DOCTEST_CHECK((doubleValues.scalar_type() == torch::kFloat64));

    network->to(torch::kFloat32);

    if (!torch::cuda::is_available())
    {
        DOCTEST_MESSAGE("CUDA unavailable; CPU and dtype moves checked");
        return;
    }

    const auto [cpuLogits, cpuValues] = network->forward(batch);

    network->to(torch::kCUDA);

    for (const auto& parameter : network->parameters())
    {
        DOCTEST_CHECK(parameter.is_cuda());
    }

    DOCTEST_CHECK_THROWS_AS(network->forward(batch), c10::Error);

    const auto [cudaLogits, cudaValues] =
        network->forward(batch.to(torch::kCUDA));

    DOCTEST_CHECK(cudaLogits.is_cuda());
    DOCTEST_CHECK(cudaValues.is_cuda());
    DOCTEST_CHECK(torch::allclose(cpuLogits, cudaLogits.cpu(), 1e-4, 1e-5));
    DOCTEST_CHECK(torch::allclose(cpuValues, cudaValues.cpu(), 1e-4, 1e-5));

    (cudaLogits.square().mean() + cudaValues.square().mean()).backward();

    for (const auto& parameter : network->parameters())
    {
        DOCTEST_REQUIRE(parameter.grad().defined());
        DOCTEST_CHECK(parameter.grad().is_cuda());
        DOCTEST_CHECK(torch::isfinite(parameter.grad()).all().item<bool>());
    }

    network->to(torch::kCPU);

    for (const auto& parameter : network->parameters())
    {
        DOCTEST_CHECK(parameter.device().is_cpu());
    }

    const auto [restoredLogits, restoredValues] = network->forward(batch);

    DOCTEST_CHECK(torch::equal(cpuLogits, restoredLogits));
    DOCTEST_CHECK(torch::equal(cpuValues, restoredValues));
}
