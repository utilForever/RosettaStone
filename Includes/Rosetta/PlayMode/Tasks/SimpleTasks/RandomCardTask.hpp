#ifndef ROSETTASTONE_PLAYMODE_RANDOM_CARD_TASK_HPP
#define ROSETTASTONE_PLAYMODE_RANDOM_CARD_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
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
    //! \param tags A list of game tags to filter.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomCardTask(CardType cardType, CardClass cardClass,
                            std::map<GameTag, int> tags, bool opposite = false);

    //! Constructs task with various arguments.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \param tags A list of game tags to filter.
    //! \param opposite The flag that indicates the card is for the opponent.
    explicit RandomCardTask(CardType cardType, CardClass cardClass,
                            Race race = Race::INVALID,
                            Rarity rarity = Rarity::INVALID,
                            std::map<GameTag, int> tags = {},
                            bool opposite = false);

    //! Returns card list that fits the criteria.
    //! \param source The source entity.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \param tags A list of game tags to filter.
    //! \return A list of cards that fits the criteria.
    static std::vector<Card*> GetCardList(
        Entity* source, CardType cardType = CardType::INVALID,
        CardClass cardClass = CardClass::INVALID, Race race = Race::INVALID,
        Rarity rarity = Rarity::INVALID, std::map<GameTag, int> tags = {});

    //! Returns card list that fits the criteria.
    //! \param source The source entity.
    //! \param cardClass The class of card to filter.
    //! \return A list of cards that fits the criteria (i.e., \p cardClass).
    static const std::vector<Card*>& GetCardList(
        Entity* source,
        CardClass cardClass);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    CardType m_cardType = CardType::INVALID;
    CardClass m_cardClass = CardClass::INVALID;
    Race m_race = Race::INVALID;
    Rarity m_rarity = Rarity::INVALID;
    std::map<GameTag, int> m_tags;
    bool m_opposite = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_RANDOM_TASK_HPP
