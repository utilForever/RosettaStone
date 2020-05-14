// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_FLAG_TASK_HPP
#define ROSETTASTONE_PLAYMODE_FLAG_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief FlagTask class.
//!
//! This class represents the task for checking flag and run the task.
//!
class FlagTask : public ITask
{
 public:
    //! Constructs task with given \p flag and \p toDoTask.
    //! \param flag A flag to check previous task results.
    //! \param toDoTasks A list of tasks to run depending on flag.
    explicit FlagTask(bool flag, std::vector<std::shared_ptr<ITask>> toDoTasks);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    bool m_flag = true;
    std::vector<std::shared_ptr<ITask>> m_toDoTasks;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_FLAG_TASK_HPP
