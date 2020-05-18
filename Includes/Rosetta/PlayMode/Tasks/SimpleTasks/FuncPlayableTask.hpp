// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_FUNC_ENTITY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_FUNC_ENTITY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

#include <functional>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief FuncPlayableTask class.
//!
//! This class represents the task for executing specific function and
//! storing result to playables.
//!
class FuncPlayableTask : public ITask
{
 public:
    //! Constructs task with given \p cardID.
    //! \param func The function to execute.
    explicit FuncPlayableTask(
        std::function<std::vector<Playable*>(std::vector<Playable*>)> func);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::function<std::vector<Playable*>(std::vector<Playable*>)> m_func;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_FUNC_ENTITY_TASK_HPP
