// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_PLAY_MINION_TASK_HPP
#define HEARTHSTONEPP_PLAY_MINION_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
{
//!
//! \brief PlayMinionTask class.
//!
//! This class represents the task for playing minion.
//! It summons minion and processes power.
//!
class PlayMinionTask : public ITask
{
 public:
    //! Constructs task with given \p entity.
    //! \param source A pointer to source entity to play card.
    //! \param fieldPos A value indicating where to place card.
    //! \param target A target of the card to receive power.
    PlayMinionTask(Entity* source = nullptr, int fieldPos = -1,
                   Entity* target = nullptr);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_fieldPos = -1;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_PLAY_MINION_TASK_HPP
