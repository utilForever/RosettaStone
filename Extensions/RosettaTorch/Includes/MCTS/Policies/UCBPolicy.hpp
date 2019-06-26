// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP

#include <MCTS/Policies/IPolicy.hpp>
#include <MCTS/Selection/EdgeAddon.hpp>
#include <MCTS/Selection/TreeNode.hpp>

#include <Rosetta/Actions/ActionType.hpp>

#include <array>
#include <cmath>
#include <limits>

namespace RosettaTorch::MCTS
{
class UCBPolicy : public IPolicy
{
 public:
    constexpr static double EXPLORE_WEIGHT = 0.2;

    void SetChildNode(ChildNodeMap& children)
    {
        m_children = &children;
    }

    int SelectChoice(RosettaStone::ActionType actionType,
                     const std::vector<int>& choices) override
    {
        constexpr size_t MAX_CHOICES = 16;
        std::array<std::pair<int, const EdgeAddon*>, MAX_CHOICES> choiceArray;
        size_t choicesIdx = 0;

        // Phase 1: get total chosen times, and record to 'choices'
        std::int64_t totalChosenTimes = 0;
        for (size_t i = 0; i < choices.size(); ++i)
        {
            choiceArray[choicesIdx].first = choices[i];
            choiceArray[choicesIdx].second = GetEdgeAddon(i);

            auto& item = choiceArray[choicesIdx];
            const int choice = item.first;
            const auto edgeAddon = item.second;

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

            assert(chosenTimes > 0);
            totalChosenTimes += chosenTimes;

            assert(choicesIdx < MAX_CHOICES);
            ++choicesIdx;
        }

        assert(totalChosenTimes > 0);

        // Phase 2: use UCB to make a choice
        const auto getScore = [totalChosenTimes](
                                  RosettaStone::ActionType actionType,
                                  size_t choiceIdx, size_t choiceCount,
                                  const EdgeAddon* edgeAddon) {
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

            const double exploitScore = edgeAddon->GetAverageCredit();
            assert(exploitScore >= -1.0);
            assert(exploitScore <= 1.0);

            auto chosenTimes = edgeAddon->GetChosenTimes();
            // In case another thread visited it
            if (chosenTimes > totalChosenTimes)
            {
                chosenTimes = totalChosenTimes;
            }

            const double exploreScore = std::sqrt(
                std::log(static_cast<double>(totalChosenTimes)) / chosenTimes);

            return exploitScore + exploreWeight * exploreScore;
        };

        assert(choicesIdx > 0);

        size_t bestChoice = 0;
        double bestScore = -std::numeric_limits<double>::infinity();

        for (size_t idx = 0; idx < choicesIdx; ++idx)
        {
            const double score =
                getScore(actionType, idx, choicesIdx, choiceArray[idx].second);
            if (score > bestScore)
            {
                bestChoice = idx;
                bestScore = score;
            }
        }

        return choiceArray[bestChoice].first;
    }

 private:
    const EdgeAddon* GetEdgeAddon(int choice) const
    {
        return m_children->Get(choice).first;
    }

    const ChildNodeMap* m_children = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
