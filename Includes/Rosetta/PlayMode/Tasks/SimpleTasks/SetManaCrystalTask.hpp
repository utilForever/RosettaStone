// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SET_MANA_CRYSTAL_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SET_MANA_CRYSTAL_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief SetManaCrystalTask class.
//!
//! This class represents the task for setting mana crystal of player.
//!
class SetManaCrystalTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p both.
    //! \param amount A value indicating how much to set mana crystal.
    //! \param both true if both player set mana crystal, and false otherwise.
    explicit SetManaCrystalTask(int amount, bool both = true);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    bool m_both = true;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SET_MANA_CRYSTAL_TASK_HPP
