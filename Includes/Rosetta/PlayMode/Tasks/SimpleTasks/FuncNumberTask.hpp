// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_FUNC_NUMBER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_FUNC_NUMBER_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

#include <functional>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief FuncNumberTask class.
//!
//! This class represents the task for executing specific function.
//!
class FuncNumberTask : public ITask
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to execute.
    explicit FuncNumberTask(std::function<int(Playable*)> func);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::function<int(Playable*)> m_func;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_FUNC_NUMBER_TASK_HPP
