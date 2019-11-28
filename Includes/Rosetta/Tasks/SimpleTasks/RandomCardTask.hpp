#ifndef ROSETTASTONE_RANDOM_CARD_TASK_HPP
#define ROSETTASTONE_RANDOM_CARD_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RandomCardTask class.
//!
//! This class represents the task for picking a card at random.
//!
class RandomCardTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p opposite.
    //! \param entityType The entity type to choose the random card from.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomCardTask(EntityType entityType, bool opposite = false);

    //! Constructs task with various arguments.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomCardTask(CardType cardType, CardClass cardClass,
                            Race race = Race::INVALID,
                            Rarity rarity = Rarity::INVALID,
                            bool opposite = false);

 private:
    //! Returns card list that fits the criteria.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \return A list of cards that fits the criteria.
    std::vector<Card*> GetCardList(CardType cardType = CardType::INVALID,
                                   CardClass cardClass = CardClass::INVALID,
                                   Race race = Race::INVALID,
                                   Rarity rarity = Rarity::INVALID) const;

    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    CardType m_cardType = CardType::INVALID;
    CardClass m_cardClass = CardClass::INVALID;
    Race m_race = Race::INVALID;
    Rarity m_rarity = Rarity::INVALID;
    bool m_opposite = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_RANDOM_TASK_HPP
