// Copyright (c) 2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
//!
//! \brief PlayLocationTask class.
//!
//! This class activates a location already on the battlefield.
//!
class PlayLocationTask : public ITask
{
 public:
    //! Constructs task with given \p source and \p target.
    explicit PlayLocationTask(Entity* source, Playable* target = nullptr);

 private:
    //! Processes task logic internally and returns meta data.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    std::unique_ptr<ITask> CloneImpl() override;
};
}  // namespace RosettaStone::PlayMode::PlayerTasks

#endif  // ROSETTASTONE_PLAYMODE_PLAY_LOCATION_TASK_HPP
