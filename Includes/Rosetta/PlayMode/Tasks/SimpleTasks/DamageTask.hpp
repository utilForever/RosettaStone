// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DAMAGE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DAMAGE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DamageTask class.
//!
//! This class represents the task for taking damage.
//!
class DamageTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p damage and \p isSpellDamage.
    //! \param entityType The entity type of target to take damage.
    //! \param damage A value indicating how much to take.
    //! \param isSpellDamage true if it is spell damage, and false otherwise.
    DamageTask(EntityType entityType, int damage, bool isSpellDamage = false);

    //! Constructs task with given \p entityType, \p damage, \p randomDamage and
    //! \p isSpellDamage.
    //! \param entityType The entity type of target to take damage.
    //! \param damage A value indicating how much to take.
    //! \param randomDamage A random value indicating how much to take.
    //! \param isSpellDamage true if it is spell damage, and false otherwise.
    DamageTask(EntityType entityType, int damage, int randomDamage,
               bool isSpellDamage = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_damage = 0;
    int m_randomDamage = 0;
    bool m_isSpellDamage = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DAMAGE_TASK_HPP
