// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_DESTORY_MINION_TASK_HPP
#define HEARTHSTONEPP_DESTORY_MINION_TASK_HPP

#include <hspp/Cards/Character.hpp>
#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief DestroyMinionTask class.
//!
//! This class represents the task for destroying minion.
//!
class DestroyMinionTask : public ITask
{
 public:
    //! Constructs task with given \p character.
    //! \param entity A pointer to character to destroy.
    DestroyMinionTask(Entity* entity);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Character* m_character = nullptr;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_DESTORY_MINION_TASK_HPP
