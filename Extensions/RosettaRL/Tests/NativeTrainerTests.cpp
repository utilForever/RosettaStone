// Copyright (c) 2026 Chris Ohk

#define DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES
#include <doctest/doctest.h>

#include <torch/serialize.h>

#include <RosettaRL/NativeTrainer.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <array>
#include <limits>
#include <sstream>
#include <vector>

using namespace RosettaStone;
using namespace PlayMode;
using namespace RL;

DOCTEST_TEST_CASE("[NativeTrainer] - RejectsInvalidBatchesBeforeUpdating")
{
    const auto observations =
        EncodeObservationBatch(std::array<Observation, 2>{});

    auto policy = torch::zeros({ 2, PolicySchema::NUM_ACTIONS });
    policy.select(1, PolicySchema::END_TURN).fill_(1);

    const auto outcomes = torch::zeros({ 2 });
    PolicyValueNetwork model;
    NativeTrainer trainer(model);

    trainer.TrainBatch(observations, policy, outcomes);

    std::vector<torch::Tensor> before;

    for (const auto& parameter : model->parameters())
    {
        before.push_back(parameter.detach().clone());
    }

    std::stringstream incomplete;

    torch::save(std::vector<torch::Tensor>{ observations, policy }, incomplete);

    DOCTEST_CHECK_THROWS_AS(trainer.TrainBatch(incomplete), c10::Error);
    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations[0], policy, outcomes), c10::Error);
    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, policy.narrow(1, 0, 1), outcomes),
        c10::Error);
    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, policy, outcomes.unsqueeze(1)),
        c10::Error);
    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, policy, outcomes.to(torch::kInt32)),
        c10::Error);
    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations.narrow(0, 0, 0), policy.narrow(0, 0, 0),
                           outcomes.narrow(0, 0, 0)),
        c10::Error);

    auto badPolicy = policy.clone();
    badPolicy[1][0] = std::numeric_limits<float>::quiet_NaN();

    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, badPolicy, outcomes), c10::Error);

    badPolicy[1][0] = 2;
    badPolicy[1][1] = -1;

    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, badPolicy, outcomes), c10::Error);

    badPolicy[1][1] = 0;

    DOCTEST_CHECK_THROWS_AS(
        trainer.TrainBatch(observations, badPolicy, outcomes), c10::Error);

    auto badOutcomes = outcomes.clone();

    for (const float invalid :
         { -2.0f, -0.5f, 0.5f, std::numeric_limits<float>::infinity(),
           std::numeric_limits<float>::quiet_NaN() })
    {
        DOCTEST_CAPTURE(invalid);
        badOutcomes[1] = invalid;
        DOCTEST_CHECK_THROWS_AS(
            trainer.TrainBatch(observations, policy, badOutcomes), c10::Error);
    }

    const auto after = model->parameters();

    for (std::size_t i = 0; i < after.size(); ++i)
    {
        DOCTEST_CHECK(torch::equal(before[i], after[i]));
    }

    DOCTEST_CHECK_EQ(trainer.TrainBatch(observations, policy, outcomes).step,
                     2);
}
