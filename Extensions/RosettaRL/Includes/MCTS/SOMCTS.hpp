// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_SOMCTS_HPP
#define ROSETTASTONE_TORCH_SOMCTS_HPP

#include <MCTS/Selection/Selection.hpp>
#include <MCTS/Simulation/Simulation.hpp>
#include <MCTS/Statistics/Statistics.hpp>

#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>
#include <Rosetta/PlayMode/Actions/ActionParams.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief SOMCTS class.
//!
//! This class is single observer MCTS.
//!
class SOMCTS
{
 public:
    //! Constructs MCTS with given \p tree, \p statistics and \p config.
    //! \param tree The tree of player.
    //! \param statistics The statistics of MCTS.
    //! \param config The config for neural network.
    explicit SOMCTS(TreeNode& tree, Statistics<>& statistics,
                    const Config& config);

    //! Deleted copy constructor.
    SOMCTS(const SOMCTS&) = delete;

    //! Deleted move constructor.
    SOMCTS(SOMCTS&&) noexcept = delete;

    //! Deleted copy assignment operator.
    SOMCTS& operator=(const SOMCTS&) = delete;

    //! Deleted move assignment operator.
    SOMCTS& operator=(SOMCTS&&) noexcept = delete;

    //! Returns the root node of the tree.
    //! \return The root node of the tree.
    TreeNode* GetRootNode() const;

    //! Starts iteration by initializing variables.
    void StartIteration();

    //! Performs appropriate action according to the stage.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    //! \return The flag to indicate that the iteration ends.
    bool PerformAction(const Board& board, StateValue& stateValue);

    //! Applies other actions to the game.
    void ApplyOthersActions();

    //! Finishes iteration to update credit.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    void FinishIteration(const Board& board, StateValue stateValue);

    //! Chooses action according to \p board, \p actionType and \p choices.
    //! \param board The game board.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    int ChooseAction(const Board& board, ActionType actionType,
                     ActionChoices& choices);

 private:
    //! \brief An enumerator for identifying stage.
    enum class Stage
    {
        SELECTION,
        SIMULATION
    };

    //!
    //! \brief ActionParams class.
    //!
    //! This class contains parameters to use when the game performs action.
    //!
    class ActionParams : public RosettaStone::PlayMode::ActionParams
    {
     public:
        //! Constructs ActionParams with given \p callback.
        //! \param callback The SOMCTS.
        explicit ActionParams(SOMCTS& callback);

        //! Deleted copy constructor.
        ActionParams(const ActionParams&) = delete;

        //! Deleted move constructor.
        ActionParams(ActionParams&&) noexcept = delete;

        //! Deleted copy assignment operator.
        ActionParams& operator=(const ActionParams&) = delete;

        //! Deleted move assignment operator.
        ActionParams& operator=(ActionParams&&) noexcept = delete;

        //! Initializes action parameters.
        //! \param board The game board.
        void Init(const Board& board);

        //! Returns the number according to \p actionType and \p choices.
        //! \param actionType The type of action.
        //! \param choices The choices of action.
        //! \return The index of chosen action.
        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& choices) final;

     private:
        const Board* m_board;
        SOMCTS& m_callback;
    };

    ActionParams m_actionParams;
    Stage m_stage;
    Selection m_selectionStage;
    Simulation m_simulationStage;
    Statistics<>& m_statistics;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_SOMCTS_HPP