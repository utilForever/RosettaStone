// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_INCLUDE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_INCLUDE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
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
    //! Constructs task with given \p entityType and \p excludeTypes.
    //! \param entityType The entity type of target to include.
    //! \param excludeTypes The array of entity type to exclude from included
    //! entity list.
    //! \param addFlag The flag that indicates entities add to task stack.
    explicit IncludeTask(
        EntityType entityType,
        std::vector<EntityType> excludeTypes = std::vector<EntityType>(),
        bool addFlag = false);

    //! Returns a list of entities based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source entity.
    //! \param target The target that indicates target entity.
    //! \return A list of entities based on the type of entity.
    static std::vector<Playable*> GetEntities(EntityType entityType,
                                              const Player* player,
                                              Entity* source = nullptr,
                                              Entity* target = nullptr);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<EntityType> m_excludeTypes;
    bool m_addFlag = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_INCLUDE_TASK_HPP
