// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DISCOVER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DISCOVER_TASK_HPP

#include <Rosetta/Common/Enums/ChoiceEnums.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
class DiscoverCriteria
{
 public:
    DiscoverCriteria() = default;

    explicit DiscoverCriteria(CardType _cardType, CardClass _cardClass,
                              Race _race, Rarity _rarity);

    bool Evaluate(const Card* card) const;

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
    //! \param repeat The number to repeat this task.
    //! \param keepAll The flag that indicates it keeps all cards.
    explicit DiscoverTask(CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          int repeat = 1, bool keepAll = false);

    //! Constructs task with given various parameters.
    //! \param cardIDs A list of card IDs to discover.
    //! \param choiceAction The choice action of discover effect.
    //! \param numberOfChoices The number of choices.
    //! \param doShuffle The flag that indicates it does shuffle.
    explicit DiscoverTask(const std::vector<std::string>& cardIDs,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          int numberOfChoices = 3, bool doShuffle = true);

    //! Constructs task with given \p discoverType and \p numberOfChoices.
    //! \param discoverType The type of discover.
    //! \param numberOfChoices The number of choices.
    //! \param repeat The number to repeat this task.
    //! \param doShuffle The flag that indicates it does shuffle.
    explicit DiscoverTask(DiscoverType discoverType, int numberOfChoices = 3,
                          int repeat = 1, bool doShuffle = true);

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
    //! \param repeat The number to repeat this task.
    //! \param keepAll The flag that indicates it keeps all cards.
    explicit DiscoverTask(std::vector<Card*> cards,
                          DiscoverType discoverType = DiscoverType::INVALID,
                          CardType cardType = CardType::INVALID,
                          CardClass cardClass = CardClass::INVALID,
                          Race race = Race::INVALID,
                          Rarity rarity = Rarity::INVALID,
                          ChoiceAction choiceAction = ChoiceAction::HAND,
                          int numberOfChoices = 3, bool doShuffle = true,
                          int repeat = 1, bool keepAll = false);

    //! Gets cards to choose from the sets.
    //! \param source The source entity.
    //! \param cardsForGeneration A list of cards for generation.
    //! \param cardsForOtherEffect A list of cards for other effect.
    //! \param numberOfChoices The number of choices.
    //! \param doShuffle The flag that indicates it does shuffle.
    static std::vector<int> GetChoices(const Entity* source,
                                       std::vector<Card*> cardsForGeneration,
                                       std::vector<int> cardsForOtherEffect,
                                       int numberOfChoices,
                                       bool doShuffle = true);

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
    //! \param choiceAction The choice action of discover effect.
    //! \return A list of cards to discover.
    auto Discover(const Game* game, Player* player, DiscoverType discoverType,
                  ChoiceAction& choiceAction) const
        -> std::tuple<std::vector<Card*>, std::vector<int>>;

    //! Evaluates a list of cards by the discover criteria.
    //! \param game The game context.
    //! \param player The player context.
    //! \param criteria The discover criteria.
    //! \return A list of cards to discover.
    std::vector<Card*> Discover(const Game* game, const Player* player,
                                DiscoverCriteria criteria) const;

    std::vector<Card*> m_cards;
    DiscoverType m_discoverType = DiscoverType::INVALID;
    DiscoverCriteria m_discoverCriteria;
    ChoiceAction m_choiceAction = ChoiceAction::INVALID;
    int m_numberOfChoices = 3;
    int m_repeat = 1;
    bool m_doShuffle = true;
    bool m_keepAll = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DISCOVER_TASK_HPP
