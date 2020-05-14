#ifndef ROSETTASTONE_PLAYMODE_RANDOM_MINION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_RANDOM_MINION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
using TagValue = std::tuple<GameTag, int, RelaSign>;

//!
//! \brief RandomMinionTask class.
//!
//! This class represents the task for picking minion(s) at random.
//!
class RandomMinionTask : public ITask
{
 public:
    //! Constructs task with given various arguments.
    //! \param tagValues A list of game tags, values and relation sign.
    //! \param amount The amount of minions to pick.
    //! \param opposite The flag that indicates the card is for the opponent.
    //! \param excludeSelf The flag that indicates whether to exclude self
    //! from the list.
    explicit RandomMinionTask(std::vector<TagValue> tagValues, int amount = 1,
                              bool opposite = false, bool excludeSelf = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<TagValue> m_tagValues;
    int m_amount = 0;
    bool m_opposite = false;
    bool m_excludeSelf = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_RANDOM_MINION_TASK_HPP
