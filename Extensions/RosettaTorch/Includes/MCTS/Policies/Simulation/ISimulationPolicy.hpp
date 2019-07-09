// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP

#include <MCTS/Types.hpp>

#include <Rosetta/Actions/ActionValidChecker.hpp>
#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief ChoiceGetter class.
//!
class ChoiceGetter
{
 public:
    ChoiceGetter(int choices) : m_choices(choices)
    {
        // Do nothing
    }

    size_t Size() const
    {
        return static_cast<size_t>(m_choices);
    }

    int Get(size_t idx) const
    {
        return static_cast<int>(idx);
    }

    template <typename Functor>
    void ForEachChoice(Functor&& functor) const
    {
        for (int i = 0; i < m_choices; ++i)
        {
            if (!functor(i))
            {
                return;
            }
        }
    }

 private:
    int m_choices;
};

//!
//! \brief ISimulationPolicy class.
//!
class ISimulationPolicy
{
 public:
    virtual ~ISimulationPolicy() = default;

    virtual bool IsEnableCutoff() = 0;

    virtual PlayState GetCutoffResult(const Board& board,
                                      StateValue& stateValue) = 0;

    virtual void StartAction(const Board& board,
                             const ActionValidChecker& checker) = 0;

    virtual int GetChoice(const Board& board, const ActionValidChecker& checker,
                          ActionType actionType,
                          const ChoiceGetter& getter) = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP