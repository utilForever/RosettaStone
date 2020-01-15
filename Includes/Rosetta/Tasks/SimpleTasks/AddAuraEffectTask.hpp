// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ADD_AURA_EFFECT_TASK_HPP
#define ROSETTASTONE_ADD_AURA_EFFECT_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief AddAuraEffectTask class.
//!
//! This class represents the task for applying aura effect to entity.
//!
class AddAuraEffectTask : public ITask
{
 public:
    //! Constructs task with given \p effect and \p entityType.
    //! \param effect The aura effect to apply.
    //! \param entityType The entity type of target to apply.
    AddAuraEffectTask(std::shared_ptr<IEffect> effect, EntityType entityType);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    std::shared_ptr<IEffect> m_effect;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_ADD_AURA_EFFECT_TASK_HPP
