// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MOMCTS_HPP
#define ROSETTASTONE_TORCH_MOMCTS_HPP

#include <MCTS/Statistics.h>
#include <MCTS/Policies/PlayerController.hpp>
#include <MCTS/SOMCTS.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief MOMCTS class.
//!
//! This class is multiple observer MCTS.
//!
class MOMCTS
{
 public:
    MOMCTS(TreeNode& p1Tree, TreeNode& p2Tree, Statistics<>& statistics)
        : m_player1(p1Tree, statistics), m_player2(p2Tree, statistics)
    {
        // Do nothing
    }

    void Iterate(const Game& game)
    {
        m_playerController.SetGame(game);
        m_player1.StartIteration();
        m_player2.StartIteration();

        while (true)
        {
            PlayerController::Player player =
                m_playerController.GetActionForPlayer();

            GetSOMCTS(player).StartActions();

            bool iterationEnds = false;
            StateValue stateValue;

            while (m_playerController.GetActionForPlayer() == player)
            {
                iterationEnds = GetSOMCTS(player).PerformAction(
                    m_playerController.GetPlayerView(player), stateValue);
                if (iterationEnds)
                {
                    break;
                }
            }

            if (iterationEnds)
            {
                m_player1.FinishIteration(
                    m_playerController.GetPlayerView(
                        PlayerController::Player::Player1()),
                    stateValue);
                m_player2.FinishIteration(
                    m_playerController.GetPlayerView(
                        PlayerController::Player::Player2()),
                    stateValue);

                break;
            }

            GetSOMCTS(player.Opposite())
                .ApplyOthersActions(
                    m_playerController.GetPlayerView(player.Opposite()));
        }
    }

    auto GetRootNode(PlayerController::Player player) const
    {
        return GetSOMCTS(player).GetRootNode();
    }

 private:
    SOMCTS& GetSOMCTS(PlayerController::Player player)
    {
        if (player.IsPlayer1())
        {
            return m_player1;
        }
        else
        {
            assert(player.IsPlayer2());
            return m_player2;
        }
    }

    SOMCTS const& GetSOMCTS(PlayerController::Player player) const
    {
        if (player.IsPlayer1())
        {
            return m_player1;
        }
        else
        {
            assert(player.IsPlayer2());
            return m_player2;
        }
    }

    PlayerController m_playerController;
    SOMCTS m_player1;
    SOMCTS m_player2;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MOMCTS_HPP