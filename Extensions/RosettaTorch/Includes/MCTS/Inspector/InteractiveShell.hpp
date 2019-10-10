// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP
#define ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP

#include <Agents/MCTSRunner.hpp>
#include <MCTS/Policies/NeuralNetworkStateValue.hpp>

#include <Rosetta/Actions/ActionApplyHelper.hpp>
#include <Rosetta/Games/Game.hpp>

#include <functional>

namespace RosettaTorch::MCTS
{
//!
//! \brief InteractiveShell class.
//!
//! This class is simple interactive shell for MCTS.
//!
class InteractiveShell
{
 public:
    using StartBoardGetter = std::function<Game()>;

    InteractiveShell(Agents::MCTSRunner* controller = nullptr,
                     StartBoardGetter startBoardGetter = StartBoardGetter());

    //! Deleted copy constructor.
    InteractiveShell(const InteractiveShell&) = delete;

    //! Deleted move constructor.
    InteractiveShell(InteractiveShell&&) noexcept = delete;

    //! Deleted copy assignment operator.
    InteractiveShell& operator=(const InteractiveShell&) = delete;

    //! Deleted move assignment operator.
    InteractiveShell& operator=(InteractiveShell&&) noexcept = delete;

    void SetController(Agents::MCTSRunner* controller);

    void SetConfig(const Agents::MCTSConfig& config);

    void SetStartBoardGetter(StartBoardGetter startBoardGetter);

    void DoCommand(std::istream& is, std::ostream& os);

 private:
    double GetStateValue(const Game& game) const;

    std::string GetChoiceSuggestionRate(const TreeNode* node, int choice,
                                        std::uint64_t totalChosenTimes);

    std::string GetTargetString(Character* character);

    void ShowBestNodeInfo(std::ostream& os, const TreeNode* mainNode,
                          const ActionValidChecker& actionChecker,
                          const TreeNode* node,
                          const ActionApplyHelper& actionInfoGetter, int indent,
                          bool onlyShowBestChoice = true);

    bool ShowBestSubNodeInfo(std::ostream& os, const TreeNode* mainNode,
                             const ActionValidChecker& actionChecker,
                             const TreeNode* node, int choice,
                             std::uint64_t totalChosenTimes,
                             const EdgeAddon* edgeAddon, TreeNode* child,
                             const ActionApplyHelper& actionInfoGetter,
                             int indent, bool onlyShowBestChoice = true);

    std::string GetChoiceString(const TreeNode* mainNode,
                                const ActionValidChecker& actionChecker,
                                const TreeNode* node, int choice,
                                const ActionApplyHelper& actionInfoGetter);

    void DoBest(std::istream& is, std::ostream& os);

    void DoRoot(std::istream& is, std::ostream& os);

    Agents::MCTSRunner* m_controller;
    StartBoardGetter m_startBoardGetter;
    const TreeNode* m_node;
    std::unique_ptr<NeuralNetworkStateValue> m_stateValue{};
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_INTERACTIVE_SHELL_HPP