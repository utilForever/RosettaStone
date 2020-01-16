#ifndef ROSETTASTONE_RANDOM_MINION_TASK_HPP
#define ROSETTASTONE_RANDOM_MINION_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RandomMinionTask class.
//!
//! This class represents the task for picking minion(s) at random.
//!
class RandomMinionTask : public ITask
{
 public:
    //! Constructs task with given various arguments.
    //! \param tag The game tag.
    //! \param value The value of the game tag to filter.
    //! \param amount The amount of minions to pick.
    //! \param relaSign The relation sign to filter.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomMinionTask(GameTag tag, int value, int amount = 1,
                              RelaSign relaSign = RelaSign::EQ,
                              bool opposite = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    GameTag m_gameTag = GameTag::INVALID;
    int m_value = 0;
    int m_amount = 0;
    RelaSign m_relaSign = RelaSign::EQ;
    bool m_opposite = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_RANDOM_MINION_TASK_HPP
