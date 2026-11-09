// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Agents/BatchedEvaluator.hpp>

#include <algorithm>
#include <limits>
#include <stdexcept>

using namespace RosettaStone;
using namespace PlayMode;

namespace
{
EvaluationInput Input(std::initializer_list<std::size_t> actions)
{
    EvaluationInput input;
    input.observation.turn[ObservationSchema::DECISION] =
        ObservationSchema::MAIN_ACTION;

    for (const auto action : actions)
    {
        input.legalMask.at(action) = 1;
    }

    return input;
}

class StubEvaluator final : public BatchedEvaluator
{
 public:
    std::vector<EvaluationResult> results;
    std::vector<EvaluationInput> received;
    std::size_t calls = 0;

 private:
    std::vector<EvaluationResult> EvaluateBatch(
        std::span<const EvaluationInput> inputs) override
    {
        ++calls;
        received.assign(inputs.begin(), inputs.end());

        return results;
    }
};
}  // namespace

TEST_CASE("[BatchedEvaluator] - UniformBatchMatchesSingleItems")
{
    auto inputs = std::array{ Input({ PolicySchema::END_TURN }),
                              Input({ 7, 42, PolicySchema::NUM_ACTIONS - 1 }),
                              Input({}) };
    inputs[2].legalMask.fill(1);

    UniformEvaluator evaluator;
    const auto results = evaluator.Evaluate(inputs);

    REQUIRE_EQ(results.size(), inputs.size());

    for (std::size_t row = 0; row < inputs.size(); ++row)
    {
        const auto& mask = inputs[row].legalMask;
        const auto count = std::count(mask.begin(), mask.end(), 1);
        std::vector<float> expected(PolicySchema::NUM_ACTIONS);

        for (std::size_t action = 0; action < mask.size(); ++action)
        {
            if (mask[action])
            {
                expected[action] = static_cast<float>(1.0 / count);
            }
        }

        CHECK(results[row].priors == expected);
        CHECK_EQ(results[row].value, 0.0f);

        const auto single = evaluator.Evaluate({ &inputs[row], 1 });

        REQUIRE_EQ(single.size(), 1);
        CHECK(single[0].priors == results[row].priors);
        CHECK_EQ(single[0].value, results[row].value);
    }
}

TEST_CASE("[BatchedEvaluator] - MasksAndNormalizesBackendWeights")
{
    auto inputs =
        std::array{ Input({ 2, 9, PolicySchema::NUM_ACTIONS - 1 }),
                    Input({ 2, 9 }), Input({ 2, 9 }), Input({ 2, 9 }) };
    const std::array weights{ 1.0f, 0.0f, std::numeric_limits<float>::max(),
                              std::numeric_limits<float>::denorm_min() };
    const std::array values{ 0.5f, -1.0f, 0.0f, 1.0f };
    StubEvaluator evaluator;

    for (std::size_t row = 0; row < inputs.size(); ++row)
    {
        inputs[row].observation.turn[ObservationSchema::TURN_NUMBER] =
            static_cast<std::int32_t>(row + 1);

        EvaluationResult result{ std::vector<float>(PolicySchema::NUM_ACTIONS),
                                 values[row] };
        result.priors[0] =
            1000.0f;  // Illegal mass must not affect normalization.
        result.priors[2] = weights[row];
        result.priors[9] =
            row == 0 || row == 3 ? 3.0f * weights[row] : weights[row];

        evaluator.results.push_back(result);
    }

    const auto results = evaluator.Evaluate(inputs);

    CHECK_EQ(evaluator.calls, 1);
    REQUIRE_EQ(evaluator.received.size(), inputs.size());
    REQUIRE_EQ(results.size(), inputs.size());

    for (std::size_t row = 0; row < inputs.size(); ++row)
    {
        CHECK(evaluator.received[row].observation == inputs[row].observation);
        CHECK(evaluator.received[row].legalMask == inputs[row].legalMask);

        std::vector<float> expected(PolicySchema::NUM_ACTIONS);
        expected[2] = row == 0 || row == 3 ? 0.25f : 0.5f;
        expected[9] = row == 0 || row == 3 ? 0.75f : 0.5f;

        CHECK(results[row].priors == expected);
        CHECK_EQ(results[row].value, values[row]);
    }
}

TEST_CASE("[BatchedEvaluator] - ValidatesInputsBeforeCallingBackend")
{
    StubEvaluator evaluator;

    CHECK(evaluator.Evaluate({}).empty());
    CHECK_EQ(evaluator.calls, 0);

    auto inputs = std::array{ Input({ 2 }), Input({ 9 }) };
    ++inputs[1].observation.schemaVersion;

    CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
    CHECK_EQ(evaluator.calls, 0);

    inputs[1].observation.schemaVersion = ObservationSchema::VERSION;

    for (const auto legal : { 2, 255 })
    {
        inputs[1].legalMask[0] = static_cast<std::uint8_t>(legal);

        CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
        CHECK_EQ(evaluator.calls, 0);
    }

    inputs[1].legalMask.fill(0);

    CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
    CHECK_EQ(evaluator.calls, 0);

    inputs[1].legalMask[9] = 1;
    evaluator.results.resize(inputs.size());

    for (auto& result : evaluator.results)
    {
        result.priors.resize(PolicySchema::NUM_ACTIONS);
    }

    CHECK_NOTHROW(evaluator.Evaluate(inputs));
    CHECK_EQ(evaluator.calls, 1);
}

TEST_CASE("[BatchedEvaluator] - RejectsInvalidBackendOutputs")
{
    const auto inputs = std::array{ Input({ 2 }), Input({ 9 }) };
    const EvaluationResult valid{
        std::vector<float>(PolicySchema::NUM_ACTIONS, 1.0f), 0.0f
    };
    StubEvaluator evaluator;

    for (const auto size :
         { std::size_t{ 0 }, inputs.size() - 1, inputs.size() + 1 })
    {
        evaluator.results.assign(size, valid);
        CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
    }

    evaluator.results = { valid, valid };

    for (const auto size : { std::size_t{ 0 }, PolicySchema::NUM_ACTIONS - 1,
                             PolicySchema::NUM_ACTIONS + 1 })
    {
        evaluator.results[1].priors.resize(size, 1.0f);
        CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
    }

    evaluator.results = { valid, valid };

    const auto nan = std::numeric_limits<float>::quiet_NaN();
    const auto infinity = std::numeric_limits<float>::infinity();

    for (const float value : { -1.01f, 1.01f, nan, infinity, -infinity })
    {
        evaluator.results[1].value = value;
        CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
    }

    evaluator.results = { valid, valid };

    for (const auto action : { 0, 9 })  // Validate illegal and legal entries.
    {
        for (const float prior : { -1.0f, nan, infinity, -infinity })
        {
            evaluator.results[1].priors[action] = prior;
            CHECK_THROWS_AS(evaluator.Evaluate(inputs), std::invalid_argument);
        }

        evaluator.results[1].priors[action] = 1.0f;
    }
}
