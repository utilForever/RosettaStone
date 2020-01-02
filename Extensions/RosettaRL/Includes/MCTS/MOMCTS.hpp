// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MOMCTS_HPP
#define ROSETTASTONE_TORCH_MOMCTS_HPP

#include <MCTS/Policies/PlayerController.hpp>
#include <MCTS/SOMCTS.hpp>
#include <MCTS/Statistics/Statistics.hpp>

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
    //! Constructs MCTS with given \p p1Tree, \p p2Tree, \p statistics and
    //! \p config.
    //! \param p1Tree The tree of player 1.
    //! \param p2Tree The tree of player 2.
    //! \param statistics The statistics of MCTS.
    MOMCTS(TreeNode& p1Tree, TreeNode& p2Tree, Statistics<>& statistics,
           const Config& config);

    //! Deleted copy constructor.
    MOMCTS(const MOMCTS&) = delete;

    //! Deleted move constructor.
    MOMCTS(MOMCTS&&) noexcept = delete;

    //! Deleted copy assignment operator.
    MOMCTS& operator=(const MOMCTS&) = delete;

    //! Deleted move assignment operator.
    MOMCTS& operator=(MOMCTS&&) noexcept = delete;

    //! Iterates the action until game is finished.
    template <class... StartArgs>
    void Iterate(StartArgs&&... startArgs)
    {
        m_playerController.StartEpisode(std::forward<StartArgs>(startArgs)...);
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
                m_player1.FinishIteration(
                    m_playerController.GetPlayerBoard(
                        PlayerController::Player::Player1()),
                    stateValue);
                m_player2.FinishIteration(
                    m_playerController.GetPlayerBoard(
                        PlayerController::Player::Player2()),
                    stateValue);

                break;
            }

            GetSOMCTS(player.Opponent()).ApplyOthersActions();
        }
    }

    //! Returns the root node of the tree.
    //! \param player The player controller.
    //! \return The root node of the tree.
    TreeNode* GetRootNode(PlayerController::Player player) const;

 private:
    //! Returns the single observer MCTS (non-const).
    //! \param player The player controller.
    //! \return The single observer MCTS.
    SOMCTS& GetSOMCTS(PlayerController::Player player);

    //! Returns the single observer MCTS (const).
    //! \param player The player controller.
    //! \return The single observer MCTS.
    const SOMCTS& GetSOMCTS(PlayerController::Player player) const;

    PlayerController m_playerController;
    SOMCTS m_player1;
    SOMCTS m_player2;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MOMCTS_HPP