// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP

#include <MCTS/Policies/Selection/ISelectionPolicy.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::MCTS
{
class RandomPolicy : public ISelectionPolicy
{
 public:
    int SelectChoice([[maybe_unused]] ActionType actionType,
                     ChoiceIterator choiceIter) override
    {
        constexpr size_t MAX_CHOICES = 16;
        std::array<ChoiceIterator::Item, MAX_CHOICES> choices{};
        size_t choicesIdx = 0;

        for (choiceIter.Begin(); !choiceIter.IsEnd(); choiceIter.StepNext())
        {
            choiceIter.Get(choices[choicesIdx]);
            ++choicesIdx;
        }

        const auto randIdx = Random::get<size_t>(0, choicesIdx - 1);
        return choices[randIdx].choice;
    }
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP
