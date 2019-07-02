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
    ActionValidChecker(const Game& game) : m_game(game)
    {
        // Do nothing
    }

    void Check(const Game& game);
    void Check()

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
    std::array<MainOpType, 4> m_opMap;
    size_t m_opMapSize = 0;

    std::vector<int> m_attacks;
    std::vector<int> m_playableCards;
    ActionTargets m_actionTargets;

    const Game& m_game;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_VALID_CHECKER_HPP
