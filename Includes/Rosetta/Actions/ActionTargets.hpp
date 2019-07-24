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
class ActionTargets
{
 public:
    ActionTargets();

    void Analyze(const ActionValidGetter& getter);

 private:
    void Fill(PlayerType playerType, const ActionValidGetter& getter);

    void Invalidate();

    std::array<Character*, 16> m_targets{};
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_TARGETS_HPP
