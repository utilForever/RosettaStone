// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Copy.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CopyTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
{
CopyTask::CopyTask(EntityType entityType, ZoneType zoneType, int amount,
                   bool addToStack, bool toOpponent)
    : ITask(entityType),
      m_zoneType(zoneType),
      m_amount(amount),
      m_addToStack(addToStack),
      m_toOpponent(toOpponent)
{
    // Do nothing
}

TaskStatus CopyTask::Impl(Player* player)
{
    Player* owner = m_toOpponent ? player->opponent : player;
    const IZone* targetZone = Generic::GetZone(owner, m_zoneType);

    if (!targetZone || targetZone->IsFull())
    {
        return TaskStatus::STOP;
    }

    std::vector<Playable*> result;

    if (m_entityType == EntityType::STACK)
    {
        if (player->game->taskStack.playables.empty())
        {
            return TaskStatus::STOP;
        }

        for (const auto& entity : player->game->taskStack.playables)
        {
            for (int i = 0; i < m_amount; ++i)
            {
                Playable* copied = Generic::Copy(owner, entity, m_zoneType);

                if (m_addToStack)
                {
                    result.emplace_back(copied);
                }

                if (targetZone->IsFull())
                {
                    if (m_addToStack)
                    {
                        player->game->taskStack.playables = result;
                    }

                    return TaskStatus::COMPLETE;
                }
            }
        }
    }
    else
    {
        Playable* toBeCopied;
        bool deathrattle = false;

        switch (m_entityType)
        {
            case EntityType::SOURCE:
            {
                toBeCopied = dynamic_cast<Playable*>(m_source);

                const auto enchantment = dynamic_cast<Enchantment*>(m_target);
                deathrattle =
                    m_zoneType == ZoneType::PLAY && enchantment &&
                    !enchantment->card->power.GetDeathrattleTask().empty();
                break;
            }
            case EntityType::TARGET:
            {
                toBeCopied = m_target;
                if (toBeCopied && toBeCopied->zone &&
                    toBeCopied->zone->GetType() == ZoneType::GRAVEYARD)
                {
                    deathrattle = true;
                }
                break;
            }
            case EntityType::STACK_NUM0:
            {
                toBeCopied =
                    player->game->entityList[player->game->taskStack.num[0]];
                break;
            }
            default:
                throw std::invalid_argument(
                    "CopyTask::Impl() - Invalid entity type");
        }

        if (!toBeCopied)
        {
            return TaskStatus::STOP;
        }

        for (int i = 0; i < m_amount; ++i)
        {
            Playable* copied =
                Generic::Copy(owner, toBeCopied, m_zoneType, deathrattle);

            if (m_addToStack)
            {
                result.emplace_back(copied);
            }

            if (targetZone->IsFull())
            {
                if (m_addToStack)
                {
                    player->game->taskStack.playables = result;
                }

                return TaskStatus::COMPLETE;
            }
        }
    }

    if (m_addToStack)
    {
        player->game->taskStack.playables = result;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> CopyTask::CloneImpl()
{
    return std::make_unique<CopyTask>(m_entityType, m_zoneType, m_amount,
                                      m_addToStack, m_toOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks