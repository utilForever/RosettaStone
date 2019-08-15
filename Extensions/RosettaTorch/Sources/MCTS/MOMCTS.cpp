// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/MOMCTS.hpp>

namespace RosettaTorch::MCTS
{
MOMCTS::MOMCTS(TreeNode& p1Tree, TreeNode& p2Tree, Statistics<>& statistics)
    : m_player1(p1Tree, statistics), m_player2(p2Tree, statistics)
{
    // Do nothing
}

void MOMCTS::Iterate(Game& game)
{
    m_playerController.SetGame(game);
    m_player1.StartIteration();
    m_player2.StartIteration();

    while (true)
    {
        PlayerController::Player player = m_playerController.GetPlayer();
        bool iterationEnds = false;
        StateValue stateValue;

        while (m_playerController.GetPlayer() == player)
        {
            iterationEnds = GetSOMCTS(player).PerformAction(
                m_playerController.GetPlayerBoard(player), stateValue);
            if (iterationEnds)
            {
                break;
            }
        }

        if (iterationEnds)
        {
            m_player1.FinishIteration(m_playerController.GetPlayerBoard(
                                          PlayerController::Player::Player1()),
                                      stateValue);
            m_player2.FinishIteration(m_playerController.GetPlayerBoard(
                                          PlayerController::Player::Player2()),
                                      stateValue);

            break;
        }

        GetSOMCTS(player.Opponent()).ApplyOthersActions();
    }
}

TreeNode* MOMCTS::GetRootNode(PlayerController::Player player) const
{
    return GetSOMCTS(player).GetRootNode();
}

SOMCTS& MOMCTS::GetSOMCTS(PlayerController::Player player)
{
    if (player.IsPlayer1())
    {
        return m_player1;
    }
    else
    {
        return m_player2;
    }
}

const SOMCTS& MOMCTS::GetSOMCTS(PlayerController::Player player) const
{
    if (player.IsPlayer1())
    {
        return m_player1;
    }
    else
    {
        return m_player2;
    }
}
}  // namespace RosettaTorch::MCTS