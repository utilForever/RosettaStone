// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP

#include <MCTS/Commons/Types.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionValidChecker.hpp>
#include <Rosetta/PlayMode/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief ChoiceGetter class.
//!
//! This class contains getter methods for action choices.
//!
class ChoiceGetter
{
 public:
    //! Constructs choice iterator with given \p choices.
    //! \param choices The number of choice.
    explicit ChoiceGetter(int choices);

    //! Returns the size of choice.
    //! \return The size of choice.
    std::size_t Size() const;

    //! Returns the value of choice at \p idx.
    //! \param idx The index of action choices.
    //! \return The value of choice at \p idx.
    int Get(std::size_t idx) const;

    //! Runs \p functor on each choice of action choices.
    //! \param functor A function to run for each choice.
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
//! This class is policy interface for simulation stage.
//!
class ISimulationPolicy
{
 public:
    //! Default virtual destructor.
    virtual ~ISimulationPolicy() = default;

    //! Returns the flag indicates whether cutoff is enabled.
    //! \return The flag indicates whether cutoff is enabled.
    virtual bool IsEnableCutoff() = 0;

    //! Returns the result of game according to cutoff.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    //! \return The result of game according to cutoff.
    virtual bool GetCutoffResult(const Board& board,
                                 StateValue& stateValue) = 0;

    //! Starts action according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    virtual void StartAction(const Board& board,
                             const ActionValidChecker& checker) = 0;

    //! Returns the choice according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    //! \param actionType The type of action.
    //! \param getter The choice getter.
    //! \return The choice according to the policy.
    virtual int GetChoice(const Board& board, const ActionValidChecker& checker,
                          ActionType actionType,
                          const ChoiceGetter& getter) = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP