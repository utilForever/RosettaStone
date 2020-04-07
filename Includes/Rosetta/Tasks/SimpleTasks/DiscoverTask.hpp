// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_DISCOVER_TASK_HPP
#define ROSETTASTONE_DISCOVER_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//! The type of discover.
enum class DiscoverType
{
    INVALID,
};

class DiscoverCriteria
{
 public:
    DiscoverCriteria() = default;

    explicit DiscoverCriteria(CardType _cardType, CardClass _cardClass,
                              Race _race, Rarity _rarity);

    bool Evaluate(Card* card) const;

    CardType cardType = CardType::INVALID;
    CardClass cardClass = CardClass::INVALID;
    Race race = Race::INVALID;
    Rarity rarity = Rarity::INVALID;
};

//!
//! \brief DiscoverTask class.
//!
//! This class represents the task for running 'Discover' effect.
//!
class DiscoverTask : public ITask
{
 public:
    //! Constructs task with given various parameters.
    //! \param cardType The type of card to discover.
    //! \param cardClass The class of card to discover.
    //! \param race The race of card to discover.
    //! \param rarity The rarity of card to discover.
    //! \param choiceAction The choice action of discover effect.
    //! \param keepAll The flag that indicates it keeps all cards.
    explicit DiscoverTask(CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          bool keepAll = false);

    //! Constructs task with given various parameters.
    //! \param cardIDs A list of card IDs to discover.
    //! \param choiceAction The choice action of discover effect.
    //! \param numberOfChoices The number of choices.
    //! \param doShuffle The flag that indicates it does shuffle.
    explicit DiscoverTask(const std::vector<std::string>& cardIDs,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          int numberOfChoices = 3, bool doShuffle = true);

    //! Constructs task with given \p discoverType.
    //! \param discoverType The type of discover.
    explicit DiscoverTask(DiscoverType discoverType);

    //! Constructs task with given various parameters.
    //! \param cards A list of cards to discover.
    //! \param discoverType The type of discover.
    //! \param cardType The type of card to discover.
    //! \param cardClass The class of card to discover.
    //! \param race The race of card to discover.
    //! \param rarity The rarity of card to discover.
    //! \param choiceAction The choice action of discover effect.
    //! \param numberOfChoices The number of choices.
    //! \param doShuffle The flag that indicates it does shuffle.
    //! \param keepAll The flag that indicates it keeps all cards.
    explicit DiscoverTask(std::vector<Card*> cards,
                          DiscoverType discoverType = DiscoverType::INVALID,
                          CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          int numberOfChoices = 3, bool doShuffle = true,
                          bool keepAll = false);

    //! Gets cards to choose from the sets.
    //! \param cardsToDiscover A list of cards to discover.
    //! \param numberOfChoices The number of choices.
    std::vector<Card*> GetChoices(std::vector<Card*> cardsToDiscover,
                                  std::size_t numberOfChoices) const;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Evaluates a list of cards by the discover type.
    //! \param game The game context.
    //! \param player The player context.
    //! \param discoverType The type of discover.
    //! \return A list of cards to discover.
    std::vector<Card*> Discover(Game* game, Player* player,
                                DiscoverType discoverType) const;

    //! Evaluates a list of cards by the discover criteria.
    //! \param game The game context.
    //! \param player The player context.
    //! \param criteria The discover criteria.
    //! \return A list of cards to discover.
    std::vector<Card*> Discover(Game* game, Player* player,
                                DiscoverCriteria criteria) const;

    std::vector<Card*> m_cards;

    DiscoverType m_discoverType = DiscoverType::INVALID;
    DiscoverCriteria m_discoverCriteria;
    ChoiceAction m_choiceAction = ChoiceAction::INVALID;
    std::size_t m_numberOfChoices = 3;
    bool m_doShuffle = true;
    bool m_keepAll = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_DISCOVER_TASK_HPP
