// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_DISCOVER_TASK_HPP
#define ROSETTASTONE_DISCOVER_TASK_HPP

#include <Rosetta/Enums/DiscoverEnums.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
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
    explicit DiscoverTask(CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND);

    //! Constructs task with given \p cardIDs and \p choiceAction.
    //! \param cardIDs A list of card IDs to discover.
    //! \param choiceAction The choice action of discover effect.
    explicit DiscoverTask(const std::vector<std::string>& cardIDs,
                          ChoiceAction choiceAction = ChoiceAction::HAND);

    //! Constructs task with given various parameters.
    //! \param cards A list of cards to discover.
    //! \param cardType The type of card to discover.
    //! \param cardClass The class of card to discover.
    //! \param race The race of card to discover.
    //! \param rarity The rarity of card to discover.
    //! \param choiceAction The choice action of discover effect.
    explicit DiscoverTask(std::vector<Card*> cards,
                          CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND);

    //! Gets cards to choose from the sets.
    //! \param cardsToDiscover A list of cards to discover.
    //! \param numberOfChoices The number of choices.
    std::vector<Card*> GetChoices(std::vector<Card*> cardsToDiscover,
                                  std::size_t numberOfChoices);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Evaluates a list of cards by the format type and the discover criteria.
    //! \param format The format type.
    //! \param criteria The discover criteria.
    //! \return A list of cards to discover.
    std::vector<Card*> Discover(FormatType format, DiscoverCriteria criteria);

    std::vector<Card*> m_cards;

    DiscoverType m_discoverType = DiscoverType::INVALID;
    DiscoverCriteria m_discoverCriteria;
    ChoiceAction m_choiceAction = ChoiceAction::INVALID;
    std::size_t m_numberOfChoices = 3;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_DISCOVER_TASK_HPP
