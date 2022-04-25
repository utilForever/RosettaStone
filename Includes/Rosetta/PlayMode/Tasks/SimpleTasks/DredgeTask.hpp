// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DREDGE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DREDGE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DredgeTask class.
//!
//! This class represents the task for processing keyword 'Dredge'.
//! Dredge is a mechanic introduced in Voyage to the Sunken City. Dredge allows
//! the player to look at the bottom 3 cards from their deck, then choose one to
//! put them on the top of their deck. Dredge can also be considered a Putting
//! on deck mechanic.
//!
class DredgeTask : public ITask
{
 public:
    //! Constructs task with given \p addToStack.
    //! \param addToStack The flag that indicates the dredged card
    //! add to task stack.
    explicit DredgeTask(bool addToStack = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DREDGE_TASK_HPP
