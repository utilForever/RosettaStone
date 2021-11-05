// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DRAW_MINION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DRAW_MINION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//! The type of draw minion task.
enum class DrawMinionType
{
    DEFAULT,       //!< Don't care.
    LOWEST_COST,   //!< Lowest cost card.
    HIGHEST_COST,  //!< Highest cost card.
    DEATHRATTLE,   //!< Has Deathrattle.
};

//!
//! \brief DrawMinionTask class.
//!
//! This class represents the task for drawing minion card(s) from the deck.
//!
class DrawMinionTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p addToStack.
    //! \param amount The amount to draw minion card(s).
    //! \param addToStack A flag to store card to stack.
    explicit DrawMinionTask(int amount, bool addToStack);

    //! Constructs task with given \p drawMinionType, \p amount
    //! and \p addToStack.
    //! \param drawMinionType The type of draw minion task.
    //! \param amount The amount to draw minion card(s).
    //! \param addToStack A flag to store card to stack.
    explicit DrawMinionTask(DrawMinionType drawMinionType, int amount,
                            bool addToStack);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    DrawMinionType m_drawMinionType = DrawMinionType::DEFAULT;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DRAW_MINION_TASK_HPP
