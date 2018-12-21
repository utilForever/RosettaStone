// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_COMBAT_TASK_HPP
#define HEARTHSTONEPP_COMBAT_TASK_HPP

#include <hspp/Tasks/Requirement.hpp>
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
    //! Constructs task with given \p agent.
    //! \param agent The task agent that is required to the requirement.
    //! \param source A pointer to source character to combat.
    //! \param target A pointer to target character to combat.
    CombatTask(TaskAgent& agent, Entity* source, Entity* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    //! Calculates index of the source and the target.
    //! \param player The player to run task.
    //! \return A tuple consisting of source and target index.
    std::tuple<BYTE, BYTE> CalculateIndex(Player& player) const;

    Requirement m_requirement;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_COMBAT_TASK_HPP
