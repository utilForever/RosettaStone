// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Agents/BatchedEvaluator.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace RosettaStone::PlayMode
{
std::vector<EvaluationResult> BatchedEvaluator::Evaluate(
    std::span<const EvaluationInput> inputs)
{
    if (inputs.empty())
    {
        return {};
    }

    for (const auto& input : inputs)
    {
        if (input.observation.schemaVersion != ObservationSchema::VERSION)
        {
            throw std::invalid_argument(
                "Invalid evaluator observation version");
        }

        const auto& mask = input.legalMask;

        if (std::any_of(mask.begin(), mask.end(),
                        [](auto legal) { return legal > 1; }) ||
            std::none_of(mask.begin(), mask.end(),
                         [](auto legal) { return legal != 0; }))
        {
            throw std::invalid_argument("Invalid evaluator legal mask");
        }
    }

    auto results = EvaluateBatch(inputs);

    if (results.size() != inputs.size())
    {
        throw std::invalid_argument("Invalid evaluator batch size");
    }

    for (std::size_t row = 0; row < inputs.size(); ++row)
    {
        auto& result = results[row];
        const auto& mask = inputs[row].legalMask;

        if (result.priors.size() != PolicySchema::NUM_ACTIONS)
        {
            throw std::invalid_argument("Invalid evaluator policy shape");
        }

        if (!std::isfinite(result.value) || result.value < -1.0f ||
            result.value > 1.0f)
        {
            throw std::invalid_argument("Invalid evaluator value");
        }

        double total = 0.0;
        std::size_t count = 0;

        for (std::size_t action = 0; action < result.priors.size(); ++action)
        {
            auto& prior = result.priors[action];

            if (!std::isfinite(prior) || prior < 0.0f)
            {
                throw std::invalid_argument("Invalid evaluator prior");
            }

            if (mask[action])
            {
                total += prior;
                ++count;
            }
            else
            {
                prior = 0.0f;
            }
        }

        for (std::size_t action = 0; action < result.priors.size(); ++action)
        {
            if (mask[action])
            {
                result.priors[action] = static_cast<float>(
                    total > 0.0 ? result.priors[action] / total : 1.0 / count);
            }
        }
    }

    return results;
}

std::vector<EvaluationResult> UniformEvaluator::EvaluateBatch(
    std::span<const EvaluationInput> inputs)
{
    std::vector<EvaluationResult> results(inputs.size());

    for (auto& result : results)
    {
        result.priors.assign(PolicySchema::NUM_ACTIONS, 1.0f);
    }

    return results;
}
}  // namespace RosettaStone::PlayMode
