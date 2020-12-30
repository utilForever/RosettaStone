// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CONSECUTIVE_DAMAGE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CONSECUTIVE_DAMAGE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ConsecutiveDamageTask class.
//!
//! This class represents the task for taking damages consecutively.
//!
class ConsecutiveDamageTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p damages and \p isSpellDamage.
    //! \param entityType The entity type of target to take damages.
    //! \param damages A list of values indicating how much to take.
    //! \param isSpellDamage true if it is spell damage, and false otherwise.
    ConsecutiveDamageTask(EntityType entityType, std::vector<int> damages,
                          bool isSpellDamage = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<int> m_damages{};
    bool m_isSpellDamage = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_CONSECUTIVE_DAMAGE_TASK_HPP
