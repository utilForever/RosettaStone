// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_POISONOUS_TASK_HPP
#define HEARTHSTONEPP_POISONOUS_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief PoisonousTask class.
//!
//! This class represents the task for dealing with poisonous ability in combat.
//!
class PoisonousTask : public ITask
{
 public:
    //! Constructs task with given \p target.
    //! \param target A pointer to attacked character.
    PoisonousTask(Character* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Character* m_target = nullptr;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_POISONOUS_TASK_HPP
