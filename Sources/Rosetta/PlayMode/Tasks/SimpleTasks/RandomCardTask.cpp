// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomCardTask.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomCardTask::RandomCardTask(EntityType entityType, bool opposite)
    : ITask(entityType), m_opposite(opposite)
{
    // Do nothing
}

RandomCardTask::RandomCardTask(CardType cardType, CardClass cardClass,
                               std::map<GameTag, int> tags, bool opposite)
    : m_cardType(cardType),
      m_cardClass(cardClass),
      m_tags(std::move(tags)),
      m_opposite(opposite)
{
    // Do nothing
}

RandomCardTask::RandomCardTask(CardType cardType, CardClass cardClass,
                               Race race, Rarity rarity,
                               std::map<GameTag, int> tags, bool opposite)
    : m_cardType(cardType),
      m_cardClass(cardClass),
      m_race(race),
      m_rarity(rarity),
      m_tags(std::move(tags)),
      m_opposite(opposite)
{
    // Do nothing
}

std::vector<Card*> RandomCardTask::GetCardList(Entity* source,
                                               CardType cardType,
                                               CardClass cardClass, Race race,
                                               Rarity rarity,
                                               std::map<GameTag, int> tags)
{
    std::vector<Card*> result;

    const auto cards = GetCardList(source, cardClass);
    for (const auto& card : cards)
    {
        if ((cardType == CardType::INVALID ||
             cardType == card->GetCardType()) &&
            (race == Race::INVALID || race == card->GetRace()) &&
            (rarity == Rarity::INVALID || rarity == card->GetRarity()))
        {
            bool check = true;

            for (auto& tag : tags)
            {
                if (!card->HasGameTag(tag.first) ||
                    card->gameTags[tag.first] != tag.second)
                {
                    check = false;
                    break;
                }
            }

            if (cardClass == CardClass::ANOTHER_CLASS && 
                (card->GetCardClass() == CardClass::NEUTRAL || 
                 source->player->GetHero()->card->GetCardClass() == 
                     card->GetCardClass()))
            {
                check = false;
            }

            if (check)
            {
                result.emplace_back(card);
            }
        }
    }

    return result;
}

const std::vector<Card*>& RandomCardTask::GetCardList(
    Entity* source, CardClass cardClass)
{
    if (cardClass == CardClass::INVALID ||
        cardClass == CardClass::ANOTHER_CLASS)
    {
        return source->game->GetFormatType() == FormatType::STANDARD
           ? Cards::GetAllStandardCards()
           : Cards::GetAllWildCards();
    }
    else if (cardClass == CardClass::PLAYER_CLASS)
    {
        const auto playerClass =
            source->player->GetHero()->card->GetCardClass();
        return source->game->GetFormatType() == FormatType::STANDARD
           ? Cards::GetStandardCards(playerClass)
           : Cards::GetWildCards(playerClass);
    }
    else
    {
        return source->game->GetFormatType() == FormatType::STANDARD
           ? Cards::GetStandardCards(cardClass)
           : Cards::GetWildCards(cardClass);
    }
}

TaskStatus RandomCardTask::Impl(Player* player)
{
    CardClass cardClass;

    switch (m_entityType)
    {
        case EntityType::HERO:
            cardClass = player->GetHero()->card->GetCardClass();
            break;
        case EntityType::ENEMY_HERO:
            cardClass = player->opponent->GetHero()->card->GetCardClass();
            break;
        case EntityType::INVALID:
            cardClass = m_cardClass;
            break;
        default:
            throw std::invalid_argument(
                "RandomCardTask::Impl() - Invalid entity type");
    }

    auto cardsList =
        GetCardList(m_source, m_cardType, cardClass, m_race, m_rarity, m_tags);
    if (cardsList.empty())
    {
        return TaskStatus::STOP;
    }

    player->game->taskStack.playables.clear();
    const auto idx = Random::get<std::size_t>(0, cardsList.size() - 1);
    auto card = Entity::GetFromCard(m_opposite ? player->opponent : player,
                                    cardsList.at(idx));
    player->game->taskStack.playables.emplace_back(card);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomCardTask::CloneImpl()
{
    auto clonedTask = std::make_unique<RandomCardTask>(
        m_cardType, m_cardClass, m_race, m_rarity, m_tags, m_opposite);
    clonedTask->m_entityType = m_entityType;

    return clonedTask;
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
