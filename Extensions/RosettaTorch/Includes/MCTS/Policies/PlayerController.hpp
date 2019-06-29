// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP
#define ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief PlayerController class.
//!
class PlayerController
{
 public:
    class Player
    {
     public:
        static constexpr Player Player1()
        {
            return Player(RosettaStone::PlayerType::PLAYER1);
        }

        static constexpr Player Player2()
        {
            return Player(RosettaStone::PlayerType::PLAYER2);
        }

        explicit constexpr Player(RosettaStone::PlayerType playerType)
            : m_playerType(playerType)
        {
            // Do nothing
        }

        bool operator==(const Player& rhs) const
        {
            return m_playerType == rhs.m_playerType;
        }

        bool operator!=(const Player& rhs) const
        {
            return m_playerType != rhs.m_playerType;
        }

        Player Opposite() const
        {
            return Player(m_playerType == RosettaStone::PlayerType::PLAYER1
                              ? RosettaStone::PlayerType::PLAYER2
                              : RosettaStone::PlayerType::PLAYER1);
        }

        bool IsPlayer1() const
        {
            return m_playerType == RosettaStone::PlayerType::PLAYER1;
        }

        bool IsPlayer2() const
        {
            return m_playerType == RosettaStone::PlayerType::PLAYER2;
        }

        RosettaStone::PlayerType GetPlayerType() const
        {
            return m_playerType;
        }

     private:
        RosettaStone::PlayerType m_playerType;
    };

    template <class StartBoardGetter>
    void StartEpisode(StartBoardGetter&& startBoardGetter)
    {
        // Do nothing
    }

    Player GetActionForPlayer()
    {
        return Player(m_game->GetCurrentPlayer().playerType);
    }

    auto GetPlayerView(Player player)
    {
        return RosettaStone::Board(*m_game, player.GetPlayerType());
    }

 private:
    RosettaStone::Game* m_game = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP