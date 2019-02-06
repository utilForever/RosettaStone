// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_COMBAT_TASK_HPP
#define HEARTHSTONEPP_COMBAT_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
{
//!
//! \brief CombatTask class.
//!
//! This class represents the task for combating between two characters.
//!
class CombatTask : public ITask
{
 public:
    //! Construct task with given \p source and \p target.
    //! \param source A pointer to source character to combat.
    //! \param target A pointer to target character to combat.
    CombatTask(Entity* source, Entity* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    //! Calculates index of the source and the target.
    //! \param player The player to run task.
    //! \return A tuple consisting of source and target index.
    std::tuple<BYTE, BYTE> CalculateIndex(Player& player) const;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_COMBAT_TASK_HPP
