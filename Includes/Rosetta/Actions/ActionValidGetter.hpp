// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_VALID_GETTER_HPP
#define ROSETTASTONE_ACTION_VALID_GETTER_HPP

#include <Rosetta/Games/Game.hpp>

#include <functional>

namespace RosettaStone
{
//!
//! \brief ActionValidGetter class.
//!
class ActionValidGetter
{
 public:
    ActionValidGetter(const Game& game);

    Hero* GetHero(PlayerType playerType) const;

    void ForEachMinion(PlayerType playerType,
                       const std::function<void(Minion*)>& func) const;

    void ForEachPlayableCard(const std::function<bool(Entity*)>& func) const;

    void ForEachAttacker(const std::function<bool(Character*)>& func) const;

    bool CanUseHeroPower() const;

 private:
    bool IsPlayable(Entity* entity) const;

    const Game& m_game;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_VALID_CHECKER_HPP
