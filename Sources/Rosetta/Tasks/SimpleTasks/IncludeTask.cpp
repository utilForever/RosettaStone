// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <stdexcept>

namespace RosettaStone::SimpleTasks
{
TaskID IncludeTask::GetTaskID() const
{
    return TaskID::INCLUDE;
}

std::vector<Entity*> IncludeTask::GetEntities(EntityType entityType,
                                              Player& player, Entity* source,
                                              Entity* target)
{
    std::vector<Entity*> entities;

    switch (entityType)
    {
        case EntityType::SOURCE:
            entities.emplace_back(source);
            break;
        case EntityType::TARGET:
            entities.emplace_back(target);
            break;
        case EntityType::ALL:
            for (auto& minion : player.GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetHero());
            for (auto& minion : player.GetOpponent().GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetOpponent().GetHero());
            break;
        case EntityType::FRIENDS:
            for (auto& minion : player.GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetHero());
            break;
        case EntityType::ENEMIES:
            for (auto& minion : player.GetOpponent().GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            entities.emplace_back(player.GetOpponent().GetHero());
            break;
        case EntityType::ENEMIES_NOTARGET:
            if (target == player.GetOpponent().GetHero())
            {
                for (auto& minion :
                     player.GetOpponent().GetField().GetAllMinions())
                {
                    entities.emplace_back(minion);
                }
            }
            else
            {
                for (auto& minion :
                     player.GetOpponent().GetField().GetAllMinions())
                {
                    if (target == minion)
                    {
                        continue;
                    }

                    entities.emplace_back(minion);
                }

                entities.emplace_back(player.GetOpponent().GetHero());
            }
            break;
        case EntityType::HERO:
            entities.emplace_back(player.GetHero());
            break;
        case EntityType::ENEMY_HERO:
            entities.emplace_back(player.GetOpponent().GetHero());
            break;
        case EntityType::WEAPON:
            if (player.GetHero()->weapon != nullptr)
            {
                entities.emplace_back(player.GetHero()->weapon);
            }
            break;
        case EntityType::ENEMY_WEAPON:
            if (player.GetOpponent().GetHero()->weapon != nullptr)
            {
                entities.emplace_back(player.GetOpponent().GetHero()->weapon);
            }
            break;
        case EntityType::HAND:
            for (auto& card : player.GetHand().GetAllCards())
            {
                entities.emplace_back(card);
            }
            break;
        case EntityType::ALL_MINIONS:
            for (auto& minion : player.GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            for (auto& minion : player.GetOpponent().GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::MINIONS:
            for (auto& minion : player.GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::ENEMY_MINIONS:
            for (auto& minion : player.GetOpponent().GetField().GetAllMinions())
            {
                entities.emplace_back(minion);
            }
            break;
        case EntityType::STACK:
            entities = player.GetGame()->taskStack.entities;
            break;
        default:
            throw std::domain_error(
                "IncludeTask::GetEntities() - Invalid entity type");
    }

    return entities;
}

TaskStatus IncludeTask::Impl(Player&)
{
    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
