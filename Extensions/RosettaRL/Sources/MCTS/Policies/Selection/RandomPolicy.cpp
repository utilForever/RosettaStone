// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Selection/RandomPolicy.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::MCTS
{
int RandomPolicy::SelectChoice(
    [[maybe_unused]] RosettaStone::ActionType actionType,
    ChoiceIterator choiceIter)
{
    constexpr std::size_t MAX_CHOICES = 16;
    std::array<ChoiceIterator::Item, MAX_CHOICES> choices{};
    std::size_t choicesIdx = 0;

    for (choiceIter.Begin(); !choiceIter.IsEnd(); choiceIter.StepNext())
    {
        choiceIter.Get(choices[choicesIdx]);
        ++choicesIdx;
    }

    const auto randIdx = Random::get<std::size_t>(0, choicesIdx - 1);
    return choices[randIdx].choice;
}
}  // namespace RosettaTorch::MCTS