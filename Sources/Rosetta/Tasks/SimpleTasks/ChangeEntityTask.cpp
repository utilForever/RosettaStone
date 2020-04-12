// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeEntityTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
ChangeEntityTask::ChangeEntityTask(EntityType entityType, CardType cardType,
                                   CardClass cardClass, Race race,
                                   Rarity rarity, const std::string& cardID,
                                   bool removeEnchantments, bool useRandomCard)
    : ITask(entityType),
      m_cardType(cardType),
      m_cardClass(cardClass),
      m_race(race),
      m_rarity(rarity),
      m_card(Cards::FindCardByID(cardID)),
      m_removeEnchantments(removeEnchantments),
      m_useRandomCard(useRandomCard)
{
    // Do nothing
}

ChangeEntityTask::ChangeEntityTask(EntityType entityType, CardType cardType,
                                   CardClass cardClass, Race race,
                                   Rarity rarity, bool removeEnchantments)
    : ITask(entityType),
      m_cardType(cardType),
      m_cardClass(cardClass),
      m_race(race),
      m_rarity(rarity),
      m_removeEnchantments(removeEnchantments),
      m_useRandomCard(true)
{
    // Do nothing
}

ChangeEntityTask::ChangeEntityTask(const std::string& cardID,
                                   EntityType entityType)
    : ITask(entityType), m_card(Cards::FindCardByID(cardID))
{
    // Do nothing
}

TaskStatus ChangeEntityTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    if (m_useRandomCard)
    {
        auto randCards = RandomCardTask::GetCardList(
            m_source, m_cardType, m_cardClass, m_race, m_rarity);

        for (auto& playable : playables)
        {
            const auto idx = Random::get<std::size_t>(0, randCards.size() - 1);
            Card* card = randCards[idx];

            Generic::ChangeEntity(player, playable, card, m_removeEnchantments);
        }

        return TaskStatus::COMPLETE;
    }

    for (auto& playable : playables)
    {
        Generic::ChangeEntity(player, playable, m_card, m_removeEnchantments);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ChangeEntityTask::CloneImpl()
{
    return std::make_unique<ChangeEntityTask>(
        m_entityType, m_cardType, m_cardClass, m_race, m_rarity,
        m_card != nullptr ? m_card->id : "", m_removeEnchantments,
        m_useRandomCard);
}
}  // namespace RosettaStone::SimpleTasks
