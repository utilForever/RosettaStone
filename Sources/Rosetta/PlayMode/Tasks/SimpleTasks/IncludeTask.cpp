// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
IncludeTask::IncludeTask(EntityType entityType,
                         std::vector<EntityType> excludeTypes, bool addFlag)
    : ITask(entityType),
      m_excludeTypes(std::move(excludeTypes)),
      m_addFlag(addFlag)
{
    // Do nothing
}

std::vector<Playable*> IncludeTask::GetEntities(EntityType entityType,
                                                const Player* player,
                                                Entity* source, Entity* target)
{
    std::vector<Playable*> entities;

    switch (entityType)
    {
        case EntityType::SOURCE:
            if (source)
            {
                entities.emplace_back(dynamic_cast<Playable*>(source));
            }
            break;
        case EntityType::TARGET:
            if (target)
            {
                entities.emplace_back(dynamic_cast<Playable*>(target));
            }
            break;
        case EntityType::ALL:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::ALL_NOSOURCE:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::FRIENDS:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->GetHero());
            break;
        case EntityType::ENEMIES:
            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::ENEMIES_NOTARGET:
            if (target == player->opponent->GetHero())
            {
                for (const auto& minion :
                     player->opponent->GetFieldZone()->GetAll())
                {
                    entities.emplace_back(minion);
                }
            }
            else
            {
                for (const auto& minion :
                     player->opponent->GetFieldZone()->GetAll())
                {
                    if (target == minion)
                    {
                        continue;
                    }

                    entities.emplace_back(minion);
                }

                entities.emplace_back(player->opponent->GetHero());
            }
            break;
        case EntityType::HERO:
            entities.emplace_back(player->GetHero());
            break;
        case EntityType::ENEMY_HERO:
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::HEROES:
            entities.emplace_back(player->GetHero());
            entities.emplace_back(player->opponent->GetHero());
            break;
        case EntityType::HERO_POWER:
            entities.emplace_back(player->GetHero()->heroPower);
            break;
        case EntityType::WEAPON:
            if (player->GetHero()->HasWeapon())
            {
                entities.emplace_back(&player->GetWeapon());
            }
            break;
        case EntityType::ENEMY_WEAPON:
            if (player->opponent->GetHero()->HasWeapon())
            {
                entities.emplace_back(&player->opponent->GetWeapon());
            }
            break;
        case EntityType::HAND:
            for (const auto& card : player->GetHandZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::HAND_SPELL:
            for (const auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::SPELL)
                {
                    entities.emplace_back(card);
                }
            }
            break;
        case EntityType::ENEMY_HAND:
            for (const auto& card : player->opponent->GetHandZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::DECK:
            for (const auto& card : player->GetDeckZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::ENEMY_DECK:
            for (const auto& card : player->opponent->GetDeckZone()->GetAll())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::ALL_MINIONS:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }

            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ALL_MINIONS_NOSOURCE:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }

            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::ALL_MINIONS_NOTARGET:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (target == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }

            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                if (target == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::ALL_MINIONS_NOEVENTSOURCE:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }

            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_NOSOURCE:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (source == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_NOEVENTSOURCE:
            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                if (player->game->currentEventData->eventSource == minion)
                {
                    continue;
                }

                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS_HAND:
            for (const auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }
            break;
        case EntityType::MINIONS_HAND_DECK_FIELD:
            for (const auto& card : player->GetHandZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }

            for (const auto& card : player->GetDeckZone()->GetAll())
            {
                if (card->card->GetCardType() == CardType::MINION)
                {
                    entities.emplace_back(card);
                }
            }

            for (const auto& minion : player->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ENEMY_MINIONS:
            for (const auto& minion :
                 player->opponent->GetFieldZone()->GetAll())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ENEMY_MINIONS_LEFTMOST:
        {
            FieldZone& opField = *(player->opponent->GetFieldZone());

            if (!opField.IsEmpty())
            {
                entities.emplace_back(opField[0]);
            }
            break;
        }
        case EntityType::ENEMY_MINIONS_RIGHTMOST:
        {
            FieldZone& opField = *(player->opponent->GetFieldZone());

            if (!opField.IsEmpty())
            {
                entities.emplace_back(opField[opField.GetCount() - 1]);
            }
            break;
        }
        case EntityType::ENEMY_SECRETS:
            for (const auto& secret :
                 player->opponent->GetSecretZone()->GetAll())
            {
                entities.emplace_back(secret);
            }
            break;
        case EntityType::GRAVEYARD:
            for (const auto& entity : player->GetGraveyardZone()->GetAll())
            {
                entities.emplace_back(entity);
            }
            break;
        case EntityType::STACK:
            entities = player->game->taskStack.playables;
            break;
        case EntityType::STACK_NUM0:
            entities.emplace_back(
                player->game->entityList[player->game->taskStack.num[0]]);
            break;
        case EntityType::STACK_NUM1:
            entities.emplace_back(
                player->game->entityList[player->game->taskStack.num[1]]);
            break;
        case EntityType::EVENT_SOURCE:
            if (const auto eventData = player->game->currentEventData.get();
                eventData)
            {
                entities.emplace_back(eventData->eventSource);
            }
            break;
        case EntityType::EVENT_TARGET:
            if (const auto eventData = player->game->currentEventData.get();
                eventData)
            {
                entities.emplace_back(eventData->eventTarget);
            }
            break;
        default:
            throw std::invalid_argument(
                "IncludeTask::GetEntities() - Invalid entity type");
    }

    return entities;
}

TaskStatus IncludeTask::Impl(Player* player)
{
    const auto entities = GetEntities(m_entityType, player, m_source, m_target);

    if (!m_excludeTypes.empty())
    {
        std::vector<Playable*> exceptEntities;

        for (const auto& excludeType : m_excludeTypes)
        {
            auto temp = GetEntities(excludeType, player, m_source, m_target);
            exceptEntities.insert(exceptEntities.end(), temp.begin(),
                                  temp.end());
        }

        std::vector<Playable*> result = entities;

        EraseIf(result, [&](const Entity* entity) {
            return std::any_of(exceptEntities.begin(), exceptEntities.end(),
                               [&](const Playable* excludeEntity) {
                                   return entity == excludeEntity;
                               });
        });

        if (m_addFlag)
        {
            player->game->taskStack.AddPlayables(result);
        }
        else
        {
            player->game->taskStack.playables = result;
        }
    }
    else if (m_addFlag)
    {
        player->game->taskStack.AddPlayables(entities);
    }
    else
    {
        player->game->taskStack.playables = entities;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> IncludeTask::CloneImpl()
{
    return std::make_unique<IncludeTask>(m_entityType, m_excludeTypes,
                                         m_addFlag);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
