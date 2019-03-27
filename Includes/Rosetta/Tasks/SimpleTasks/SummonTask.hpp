// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SUMMON_TASK_HPP
#define ROSETTASTONE_SUMMON_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief SummonTask class.
//!
//! This class represents the task for summoning minion at battlefield.
//!
class SummonTask : public ITask
{
 public:
    //! Constructs task with given \p cardID and \p num.
    //! \param cardID The card ID to summon.
    //! \param num The number of minions to summon.
    explicit SummonTask(std::string cardID, int num);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    std::string m_cardID;
    int m_num = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_SUMMON_TASK_HPP
