// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_BOARD_HPP
#define ROSETTASTONE_BOARD_HPP

#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Views/BoardRefView.hpp>

namespace RosettaStone
{
//!
//! \brief Board class.
//!
class Board
{
 public:
    Board(Game& game, PlayerType playerType);

    void RefCopyFrom(const Board& rhs);

    Player& GetCurrentPlayer() const;

    PlayerType GetViewType() const;

    ReducedBoardView CreateView() const;

    CurrentPlayerBoardRefView GetCurPlayerStateRefView() const;

    PlayState ApplyAction(ActionParams& params) const;

    const Game& RevealInfoForSimulation() const;

    template <class Functor>
    auto ApplyWithPlayerStateView(Functor&& functor) const
    {
        if (m_playerType == PlayerType::PLAYER1)
        {
            return functor(
                ReducedBoardView(BoardRefView(m_game, PlayerType::PLAYER1)));
        }
        else
        {
            return functor(
                ReducedBoardView(BoardRefView(m_game, PlayerType::PLAYER2)));
        }
    }

 private:
    Game& m_game;
    PlayerType m_playerType;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_HPP
