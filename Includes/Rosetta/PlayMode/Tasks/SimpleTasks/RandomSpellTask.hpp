#ifndef ROSETTASTONE_PLAYMODE_RANDOM_SPELL_TASK_HPP
#define ROSETTASTONE_PLAYMODE_RANDOM_SPELL_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief RandomSpellTask class.
//!
//! This class represents the task for picking spell(s) at random.
//!
class RandomSpellTask : public ITask
{
 public:
    //! Constructs task with given \p cardClass and \p amount.
    //! \param cardClass The card class to filter.
    //! \param amount The amount of spell(s) to pick.
    explicit RandomSpellTask(CardClass cardClass, int amount = 1);

    //! Constructs task with given various arguments.
    //! \param cardClass The card class to filter.
    //! \param tag The game tag.
    //! \param value The value of the game tag to filter.
    //! \param amount The amount of spell(s) to pick.
    //! \param relaSign The relation sign to filter.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomSpellTask(CardClass cardClass, GameTag tag, int value,
                             int amount = 1, RelaSign relaSign = RelaSign::EQ,
                             bool opposite = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Evaluates condition using relation sign and game tags.
    //! \param card The card to evaluate condition.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Card* card) const;

    CardClass m_cardClass = CardClass::INVALID;
    GameTag m_gameTag = GameTag::INVALID;
    int m_value = 0;
    int m_amount = 0;
    RelaSign m_relaSign = RelaSign::EQ;
    bool m_opposite = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_RANDOM_SPELL_TASK_HPP
