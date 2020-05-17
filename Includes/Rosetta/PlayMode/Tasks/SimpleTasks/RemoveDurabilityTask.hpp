#ifndef ROSETTASTONE_PLAYMODE_REMOVE_DURABILITY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_REMOVE_DURABILITY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief RemoveDurabilityTask class.
//!
//! This class represents the task for removing durability from hero's weapon.
//!
class RemoveDurabilityTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p isOpponent.
    //! \param amount The amount of durability to remove.
    //! \param isOpponent A flag to owner indicating opponent player.
    explicit RemoveDurabilityTask(int amount, bool isOpponent = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount;
    bool m_isOpponent;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_REMOVE_DURABILITY_TASK_HPP
