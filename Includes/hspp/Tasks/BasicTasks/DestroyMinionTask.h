// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_DESTORY_MINION_TASK_H
#define HEARTHSTONEPP_DESTORY_MINION_TASK_H

#include <hspp/Cards/Character.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
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
    //! \param character A pointer to character to destroy.
    DestroyMinionTask(Character* character);

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
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DESTORY_MINION_TASK_H
