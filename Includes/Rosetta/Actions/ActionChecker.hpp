// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_CHECKER_HPP
#define ROSETTASTONE_ACTION_CHECKER_HPP

#include <Rosetta/Games/Game.hpp>

namespace RosettaStone
{
//!
//! \brief ActionChecker class.
//!
class ActionChecker
{
 public:
    ActionChecker(const Game& game) : m_game(game)
    {
        // Do nothing
    }

    Hero* GetHero(PlayerType playerType) const
    {
        const auto hero = (playerType == PlayerType::PLAYER1)
                              ? m_game.GetPlayer1().GetHero()
                              : m_game.GetPlayer2().GetHero();

        return hero;
    }

    template <class Functor>
    void ForEachMinion(PlayerType playerType, Functor&& functor) const
    {
        auto& fieldZone = (playerType == PlayerType::PLAYER1)
                              ? m_game.GetPlayer1().GetFieldZone()
                              : m_game.GetPlayer2().GetFieldZone();

        for (auto& minion : fieldZone.GetAll())
        {
            functor(minion);
        }
    }

 private:
    const Game& m_game;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_CHECKER_HPP
