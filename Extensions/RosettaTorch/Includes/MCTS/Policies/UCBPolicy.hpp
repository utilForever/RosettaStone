// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP

#include "MCTS/Selection/EdgeAddon.hpp"
#include "MCTS/Selection/TreeNode.hpp"

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionType.hpp>

#include <array>
#include <cmath>
#include <limits>

namespace RosettaTorch::MCTS
{
class UCBPolicy
{
 public:
    constexpr static double EXPLORE_WEIGHT = 0.2;

    int SelectChoice(RosettaStone::ActionType actionType,
                     ChoiceIterator choiceIterator)
    {
        constexpr size_t MAX_CHOICES = 16;
        std::array<ChoiceIterator::Item, MAX_CHOICES> choices{};
        size_t choicesSize = 0;

        // Phase 1: get total chosen times, and record to 'choices'
        std::int64_t totalChosenTimes = 0;
        for (choiceIterator.Begin(); !choiceIterator.IsEnd();
             choiceIterator.StepNext())
        {
            choiceIterator.Get(choices[choicesSize]);
            auto& item = choices[choicesSize];
            int choice = item.choice;
            auto edgeAddon = item.edgeAddon;

            if (!edgeAddon)
                return choice;  // force select

            auto chosenTimes = edgeAddon->GetChosenTimes();
            if (chosenTimes == 0)
            {
                return choice;  // force select
            }
            if (edgeAddon->GetTotal() == 0)
            {
                // a node is created (from another thread),
                // but is not yet updated from that thread
                // in this case, we just force select that choice
                return choice;
            }

            assert(chosenTimes > 0);
            totalChosenTimes += chosenTimes;

            assert(choicesSize < MAX_CHOICES);
            ++choicesSize;
        }

        assert(totalChosenTimes > 0);

        // Phase 2: use UCB to make a choice
        auto getScore = [totalChosenTimes](
                             engine::ActionType action_type, size_t choice_idx,
                             size_t choice_count,
                             ChoiceIterator::Item const& item) {
            double explore_weight = kExploreWeight;
            if (action_type == engine::ActionType::kMainAction)
            {
                if (choice_idx == choice_count - 1)
                {
                    // do not choose end-turn action
                    // this is a simple mimic to policy network as in AlphaZero
                    explore_weight *= 0.1;
                }
            }

            double exploit_score = item.edge_addon->GetAverageCredit();
            assert(exploit_score >= -1.0);
            assert(exploit_score <= 1.0);

            auto chosen_times = item.edge_addon->GetChosenTimes();
            // in case another thread visited it
            if (chosen_times > totalChosenTimes)
                chosen_times = totalChosenTimes;
            double explore_score =
                std::sqrt(std::log((double)totalChosenTimes) / chosen_times);

            return exploit_score + explore_weight * explore_score;
        };

        assert(choicesSize > 0);

        size_t best_choice = 0;
        double best_score = -std::numeric_limits<double>::infinity();

        for (size_t idx = 0; idx < choicesSize; ++idx)
        {
            double score =
                getScore(action_type, idx, choicesSize, choices[idx]);
            if (score > best_score)
            {
                best_choice = idx;
                best_score = score;
            }
        }

        return (int)choices[best_choice].choice;
    }
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
