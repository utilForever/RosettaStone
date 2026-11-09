// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_BATCHED_EVALUATOR_HPP
#define ROSETTASTONE_PLAYMODE_BATCHED_EVALUATOR_HPP

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <span>
#include <vector>

namespace RosettaStone::PlayMode
{
//! One nonterminal decision, with observation and mask from the same state.
//! Owns visible, player-relative data only; no game pointers or hidden state.
struct EvaluationInput
{
    Observation observation;
    PolicySchema::LegalMask legalMask{};
};

//! One row of a policy/value batch, in the corresponding input's perspective.
//! Priors use PolicySchema indices; value is for ObservationSchema::SELF.
struct EvaluationResult
{
    std::vector<float> priors;
    float value = 0.0f;
};

//! Synchronous contract shared by search and future C++/Python backends.
//! Backends must preserve row order and produce the same results regardless
//! of batch composition. Terminal rewards bypass evaluation.
class BatchedEvaluator
{
 public:
    virtual ~BatchedEvaluator() = default;

    //! Validates every input before invoking the backend. Observations must
    //! use the current schema; masks must be binary with a legal action.
    //! Returns one row per input with NUM_ACTIONS finite, nonnegative priors
    //! and a finite value in [-1, 1]. Illegal priors become zero and legal
    //! priors are normalized; all-zero legal weights become uniform.
    //! Invalid inputs/outputs throw std::invalid_argument without returning
    //! a partial batch. Empty input returns empty output without a backend
    //! call. Single-item evaluation uses a span of length one.
    std::vector<EvaluationResult> Evaluate(
        std::span<const EvaluationInput> inputs);

 protected:
    //! Returns one row per input, with NUM_ACTIONS finite, nonnegative
    //! weights (not logits), including masked entries, and values in [-1, 1].
    //! Inputs are borrowed for this call only. Backend exceptions propagate.
    virtual std::vector<EvaluationResult> EvaluateBatch(
        std::span<const EvaluationInput> inputs) = 0;
};

//! Uniform over legal actions with zero value; consumes no randomness.
class UniformEvaluator final : public BatchedEvaluator
{
 private:
    std::vector<EvaluationResult> EvaluateBatch(
        std::span<const EvaluationInput> inputs) override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_BATCHED_EVALUATOR_HPP
