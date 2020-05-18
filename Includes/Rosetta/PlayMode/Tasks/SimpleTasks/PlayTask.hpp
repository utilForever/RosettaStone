// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//! The type of playable.
enum class PlayType
{
    SPELL
};

//!
//! \brief PlayTask class.
//!
//! This class represents the task for allowing to have a playable
//! played out in a task.
//!
class PlayTask : public ITask
{
 public:
    //! Constructs task with given \p playType and \p randTarget.
    //! \param playType The type of playable.
    //! \param randTarget True if the target of the playable is chosen randomly.
    explicit PlayTask(PlayType playType, bool randTarget = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    PlayType m_playType;
    bool m_randTarget = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_PLAY_TASK_HPP
