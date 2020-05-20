// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_JUDGES_IAGENT_HPP
#define ROSETTASTONE_TORCH_JUDGES_IAGENT_HPP

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>

namespace RosettaTorch::Judges
{
//!
//! \brief IAgent class.
//!
//! This class is interface of Agent class for judgment.
//! All classes that inherit from it must implement Think() and
//! GetAction() methods.
//!
class IAgent
{
 public:
    //! Default virtual destructor.
    virtual ~IAgent() = default;

    //! Processes something related to agent.
    //! \param view The board ref view for the current player.
    virtual void Think(BoardRefView& view) = 0;

    //! Returns action according to \p actionType and \p choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    virtual int GetAction(ActionType actionType, ActionChoices choices) = 0;
};
}  // namespace RosettaTorch::Judges

#endif  // ROSETTASTONE_TORCH_JUDGES_IAGENT_HPP