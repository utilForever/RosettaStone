// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP
#define ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP

#include <Agents/MCTSRunner.hpp>

#include <istream>
#include <ostream>

namespace RosettaTorch::MCTS
{
class InteractiveShell
{
 public:
    InteractiveShell(Agents::MCTSRunner* controller = nullptr)
        : m_controller(controller)
    {
        // Do nothing
    }

    InteractiveShell(const InteractiveShell&) = delete;
    InteractiveShell& operator=(const InteractiveShell&) = delete;

    void SetController(Agents::MCTSRunner* controller)
    {
        m_controller = controller;
    }

    void SetConfig(const Agents::MCTSConfig& config)
    {
        // Do nothing
    }

    void DoCommand(std::istream& is, std::ostream& s)
    {
        std::string cmd;
        is >> cmd;

        if (cmd == "h" || cmd == "help")
        {
            s << "Commands: " << std::endl
              << "h or help: show this message" << std::endl
              << "b or best: show the best action to do (add -v for verbose)"
              << std::endl
              << "root (1 or 2): set node to root node of player 1 or 2"
              << std::endl
              << "node (addr): set node to specified address." << std::endl;
        }
        else if (cmd == "b" || cmd == "best")
        {
            DoBest(is, s);
        }
        else if (cmd == "root")
        {
            DoRoot(is, s);
        }
        else if (cmd == "node")
        {
            uint64_t v = 0;
            is >> std::hex >> v >> std::dec;
            m_node = reinterpret_cast<TreeNode*>(v);
            s << "Node set to: " << m_node << std::endl;
        }
        else
        {
            s << "Unknown command. Type 'h' or 'help' for usage help."
              << std::endl;
        }
    }

    void DoBest(std::istream& is, std::ostream& s)
    {
        std::string strVerbose;
        if (is)
        {
            is >> strVerbose;
        }

        bool verbose;
        if (strVerbose == "-v")
        {
            verbose = true;
        }
        else if (strVerbose.empty())
        {
            verbose = false;
        }
        else
        {
            s << "Unknown option: " << strVerbose;
            return;
        }

        s << "Best action: " << std::endl;

        if (verbose)
        {
            // TODO: ...
        }

        auto node = m_controller->GetRootNode(PlayerType::PLAYER1);
        if (!node)
        {
            s << "[ERROR] no root node exists." << std::endl;
            return;
        }

        //if (!node->addon.consistency_checker.CheckActionType(
        //        engine::ActionType::kMainAction))
        //{
        //    s << "[ERROR] root node should be with type 'kMainAction'"
        //      << std::endl;
        //    return;
        //}

        //engine::ActionApplyHelper action_cb_info_getter;
        //ShowBestNodeInfo(s, node, action_analyzer, node, action_cb_info_getter,
        //                 0, !verbose);
    }

    void DoRoot(std::istream& is, std::ostream& s)
    {
        int v = 0;
        is >> v;

        RosettaStone::PlayerType playerType;
        if (v == 1)
        {
            playerType = PlayerType::PLAYER1;
        }
        else if (v == 2)
        {
            playerType = PlayerType::PLAYER2;
        }
        else
        {
            s << "invalid input" << std::endl;
            return;
        }

        m_node = m_controller->GetRootNode(playerType);
        s << "Current node set to: " << m_node << std::endl;
    }

 private:
    Agents::MCTSRunner* m_controller = nullptr;
    const TreeNode* m_node = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP