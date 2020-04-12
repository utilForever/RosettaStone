#ifndef ROSETTASTONE_RANDOM_MINION_NUMBER_TASK_HPP
#define ROSETTASTONE_RANDOM_MINION_NUMBER_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RandomMinionNumberTask class.
//!
//! This class represents the task for picking minion(s) at random
//! with the value of the game tag.
//!
class RandomMinionNumberTask : public ITask
{
 public:
    //! Constructs task with given \p tag and \p toOpponent.
    //! \param tag The game tag.
    //! \param toOpponent The flag that indicates the owner of random minion.
    explicit RandomMinionNumberTask(GameTag tag, bool toOpponent = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    GameTag m_gameTag = GameTag::INVALID;
    bool m_toOpponent = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_RANDOM_MINION_NUMBER_TASK_HPP
