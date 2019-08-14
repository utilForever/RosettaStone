// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_VALID_CHECKER_HPP
#define ROSETTASTONE_ACTION_VALID_CHECKER_HPP

#include <Rosetta/Actions/ActionTargets.hpp>
#include <Rosetta/Enums/ActionEnums.hpp>
#include <Rosetta/Games/Game.hpp>

namespace RosettaStone
{
//!
//! \brief ActionValidChecker class.
//!
class ActionValidChecker
{
 public:
    void Reset();

    void Check(const Game& game);
    void Check(const ActionValidGetter& getter);

    const std::array<MainOpType, 4>& GetMainActions() const;
    int GetMainActionsCount() const;
    const std::vector<Entity*>& GetPlayableCards() const;
    const std::vector<Character*>& GetAttackers() const;

 private:
    std::array<MainOpType, 4> m_opMap = {};
    std::size_t m_opMapSize = 0;

    std::vector<Character*> m_attackers;
    std::vector<Entity*> m_playableCards;
    ActionTargets m_actionTargets;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_VALID_CHECKER_HPP
