// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_APPLY_EFFECT_TASK_HPP
#define ROSETTASTONE_PLAYMODE_APPLY_EFFECT_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ApplyEffectTask class.
//!
//! This class represents the task for applying effect to something.
//!
class ApplyEffectTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p effects.
    //! \param entityType The entity type to apply effect.
    //! \param effects A list of effects to apply.
    explicit ApplyEffectTask(EntityType entityType,
                             std::vector<std::shared_ptr<IEffect>> effects);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<std::shared_ptr<IEffect>> m_effects;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_APPLY_EFFECT_TASK_HPP
