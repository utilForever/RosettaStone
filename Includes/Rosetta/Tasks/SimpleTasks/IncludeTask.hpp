// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_INCLUDE_TASK_HPP
#define ROSETTASTONE_INCLUDE_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief IncludeTask class.
//!
//! This class represents the task for including entities to be applied by
//! another task.
//!
class IncludeTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to include.
    explicit IncludeTask(EntityType entityType);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

    //! Returns a list of entities based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source entity.
    //! \param target The target that indicates target entity.
    //! \return A list of entities based on the type of entity.
    static std::vector<Entity*> GetEntities(EntityType entityType,
                                            Player& player,
                                            Entity* source = nullptr,
                                            Entity* target = nullptr);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_INCLUDE_TASK_HPP
