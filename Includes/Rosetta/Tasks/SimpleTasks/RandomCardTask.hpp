#ifndef ROSETTASTONE_RANDOM_CARD_TASK_HPP
#define ROSETTASTONE_RANDOM_CARD_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RandomCardTask class.
//!
//! This class represents the task for picking entities at random.
//!
class RandomCardTask : public ITask
{
 public:
    //! Constructs task with given \p cardType, \p cardClass and \p race.
    //! \param cardType The type of card.
    //! \param cardClass The class of card.
    //! \param cardRace The race of card.
    RandomCardTask(CardType cardType = CardType::INVALID,
                   CardClass cardClass = CardClass::INVALID, Race cardRace = Race::INVALID);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

    const CardType m_cardType;
    const CardClass m_cardClass;
    const Race m_cardRace;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_RANDOM_TASK_HPP
