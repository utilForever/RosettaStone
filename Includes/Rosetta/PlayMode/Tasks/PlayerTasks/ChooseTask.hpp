// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CHOOSE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CHOOSE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

#include <vector>

namespace RosettaStone::PlayMode::PlayerTasks
{
//!
//! \brief ChooseTask class.
//!
//! This class represents the task for choosing cards.
//!
class ChooseTask : public ITask
{
 public:
    //! Construct task with given \p choices.
    //! \param choices A container of card to choose.
    explicit ChooseTask(std::vector<int> choices);

    //! ChooseTask wrapper for mulligan.
    //! \param player The player to run task.
    //! \param choices A container of card to choose.
    //! \return Generated PlayCardTask for intended purpose.
    static ChooseTask Mulligan(Player* player, std::vector<int> choices);

    //! ChooseTask wrapper for pick.
    //! \param player The player to run task.
    //! \param choice A card to choose.
    //! \return Generated PlayCardTask for intended purpose.
    static ChooseTask Pick(Player* player, int choice);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<int> m_choices;
};
}  // namespace RosettaStone::PlayMode::PlayerTasks

#endif  // ROSETTASTONE_PLAYMODE_CHOOSE_TASK_HPP
