// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_PARAMS_HPP
#define ROSETTASTONE_ACTION_PARAMS_HPP

#include <Rosetta/Enums/ActionEnums.hpp>
#include <Rosetta/Models/Character.hpp>

#include <array>
#include <vector>

namespace RosettaStone
{
//!
//! \brief ActionParams class.
//!
class ActionParams
{
 public:
    void Analyze();

 private:
    std::array<MainOpType, 4> m_opMap;
    size_t m_opMapSize = 0;

    std::vector<int> m_attacks;
    std::vector<int> m_playableCards;
    std::vector<Character*> m_targets;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_PARAMS_HPP
