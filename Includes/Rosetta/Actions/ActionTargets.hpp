// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_TARGETS_HPP
#define ROSETTASTONE_ACTION_TARGETS_HPP

#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/Player.hpp>

#include <array>

namespace RosettaStone
{
class ActionValidGetter;

//!
//! \brief ActionTargets class.
//!
//! This class fills the targets such as hero and minion to perform action.
//!
class ActionTargets
{
 public:
    //! Constructs action targets by invalidating member variables.
    ActionTargets();

    //! Analyzes targets to fill target list data.
    //! \param getter The action valid getter.
    void Analyze(const ActionValidGetter& getter);

 private:
    //! Fills target list data to hero and minion.
    //! \param playerType The type of player.
    //! \param getter The action valid getter.
    void Fill(PlayerType playerType, const ActionValidGetter& getter);

    //! Invalidates member variables.
    void Invalidate();

    std::array<Character*, 16> m_targets{};
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_TARGETS_HPP
