// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Selection/UCBPolicy.hpp>

#include <cmath>

namespace RosettaTorch::MCTS
{
int UCBPolicy::SelectChoice(RosettaStone::ActionType actionType,
                            ChoiceIterator choiceIter)
{
    constexpr std::size_t MAX_CHOICES = 16;
    std::array<ChoiceIterator::Item, MAX_CHOICES> choices{};
    std::size_t choicesIdx = 0;

    // Phase 1: get total chosen times, and record to 'choices'
    std::int64_t totalChosenTimes = 0;
    for (choiceIter.Begin(); !choiceIter.IsEnd(); choiceIter.StepNext())
    {
        choiceIter.Get(choices[choicesIdx]);
        auto& item = choices[choicesIdx];
        const int choice = item.choice;
        const auto edgeAddon = item.edgeAddon;

        if (!edgeAddon)
        {
            // Force select
            return choice;
        }

        const auto chosenTimes = edgeAddon->GetChosenTimes();
        if (chosenTimes == 0)
        {
            // Force select
            return choice;
        }

        if (edgeAddon->GetTotal() == 0)
        {
            // A node is created (from another thread),
            // but is not yet updated from that thread
            // in this case, we just force select that choice
            return choice;
        }

        totalChosenTimes += chosenTimes;
        ++choicesIdx;
    }

    // Phase 2: use UCB to make a choice
    const auto getScore = [totalChosenTimes](
                              RosettaStone::ActionType actionType,
                              std::size_t choiceIdx, std::size_t choiceCount,
                              const ChoiceIterator::Item& item) {
        double exploreWeight = EXPLORE_WEIGHT;

        if (actionType == RosettaStone::ActionType::MAIN_ACTION)
        {
            if (choiceIdx == choiceCount - 1)
            {
                // Do not choose end-turn action
                // This is a simple mimic to policy network as in AlphaZero
                exploreWeight *= 0.1;
            }
        }

        const double exploitScore = item.edgeAddon->GetAverageCredit();

        auto chosenTimes = item.edgeAddon->GetChosenTimes();
        // In case another thread visited it
        if (chosenTimes > totalChosenTimes)
        {
            chosenTimes = totalChosenTimes;
        }

        const double exploreScore = std::sqrt(
            std::log(static_cast<double>(totalChosenTimes)) / chosenTimes);

        return exploitScore + exploreWeight * exploreScore;
    };

    std::size_t bestChoice = 0;
    double bestScore = -std::numeric_limits<double>::infinity();

    for (std::size_t idx = 0; idx < choicesIdx; ++idx)
    {
        const double score =
            getScore(actionType, idx, choicesIdx, choices[idx]);
        if (score > bestScore)
        {
            bestChoice = idx;
            bestScore = score;
        }
    }

    return choices[bestChoice].choice;
}
}  // namespace RosettaTorch::MCTS