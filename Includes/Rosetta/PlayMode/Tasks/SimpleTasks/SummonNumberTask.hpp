// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMON_NUMBER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SUMMON_NUMBER_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief SummonNumberTask class.
//!
//! This class represents the task for summoning minion that
//! repeats for the number in the task stack.
//!
class SummonNumberTask : public ITask
{
 public:
    //! Constructs task with given \p cardID, \p opponent and \p side.
    //! \param cardID The card ID to summon.
    //! \param opponent The flag to summon for the opponent player.
    //! \param side The side of summoned minion.
    explicit SummonNumberTask(const std::string& cardID, bool opponent,
                              SummonSide side = SummonSide::DEFAULT);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Card* m_card = nullptr;
    bool m_opponent = false;
    SummonSide m_side = SummonSide::DEFAULT;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SUMMON_NUMBER_TASK_HPP
