// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_HPP
#define HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief InitAttackCountTask class.
//!
//! This class represents the task for initializing attack count.
//!
class InitAttackCountTask : public ITask
{
 public:
    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    //! Processes attack count initialization logic of my field.
    //! \param player The my player.
    static void ProcessMyField(Player& player);

    //! Processes attack count initialization logic of opponent field.
    //! \param player The opponent player.
    static void ProcessOpField(Player& player);
};

}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_HPP
