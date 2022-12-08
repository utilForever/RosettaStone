// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
//!
//! \brief PlayLocationTask class.
//!
//! This class represents the task for playing location card from field.
//!
class PlayLocationTask : public ITask
{
 public:
    //! Construct task with given \p source and \p target.
    //! \param source A pointer to source location.
    //! \param target A pointer to target character.
    PlayLocationTask(Entity* source, Playable* target);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Character* target) const;
};
}  // namespace RosettaStone::PlayMode::PlayerTasks

#endif  // ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP
