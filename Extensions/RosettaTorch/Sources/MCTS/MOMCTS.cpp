// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/MOMCTS.hpp>

namespace RosettaTorch::MCTS
{
MOMCTS::MOMCTS(TreeNode& p1Tree, TreeNode& p2Tree, Statistics<>& statistics,
               const Config& config)
    : m_player1(p1Tree, statistics, config),
      m_player2(p2Tree, statistics, config)
{
    // Do nothing
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