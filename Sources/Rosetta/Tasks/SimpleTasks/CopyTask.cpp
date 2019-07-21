// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Copy.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>

namespace RosettaStone::SimpleTasks
{
CopyTask::CopyTask(EntityType entityType, ZoneType zoneType, int amount,
                   bool addToStack, bool toOpposite)
    : ITask(entityType),
      m_zoneType(zoneType),
      m_amount(amount),
      m_addToStack(addToStack),
      m_toOpposite(toOpposite)
{
    // Do nothing
}

TaskID CopyTask::GetTaskID() const
{
    return TaskID::COPY;
}

TaskStatus CopyTask::Impl(Player& player)
{
    Player& owner = (m_toOpposite) ? *player.opponent : player;
    IZone* targetZone = Generic::GetZone(owner, m_zoneType);

    if (targetZone == nullptr || targetZone->IsFull())
    {
        return TaskStatus::STOP;
    }

    std::vector<Entity*> result;

    if (m_entityType == EntityType::STACK)
    {
        if (player.GetGame()->taskStack.entities.empty())
        {
            return TaskStatus::STOP;
        }

        for (auto& entity : player.GetGame()->taskStack.entities)
        {
            Entity* copied = Generic::Copy(owner, entity, m_zoneType);

            if (m_addToStack)
            {
                result.emplace_back(copied);
            }

            if (targetZone->IsFull())
            {
                if (m_addToStack)
                {
                    player.GetGame()->taskStack.entities = result;
                }

                return TaskStatus::COMPLETE;
            }
        }
    }
    else
    {
        Entity* toBeCopied;
        bool deathrattle = false;

        switch (m_entityType)
        {
            case EntityType::SOURCE:
            {
                toBeCopied = m_source;

                auto enchantment = dynamic_cast<Enchantment*>(m_target);
                deathrattle =
                    (m_zoneType == ZoneType::PLAY) &&
                    (enchantment != nullptr) &&
                    (!enchantment->card.power.GetDeathrattleTask().empty());
                break;
            }
            case EntityType::TARGET:
            {
                toBeCopied = m_target;
                break;
            }
            default:
                throw std::invalid_argument(
                    "CopyTask::Impl() - Invalid entity type");                
        }

        if (toBeCopied == nullptr)
        {
            return TaskStatus::STOP;
        }

        for (int i = 0; i < m_amount; ++i)
        {
            Entity* copied =
                Generic::Copy(owner, toBeCopied, m_zoneType, deathrattle);

            if (m_addToStack)
            {
                result.emplace_back(copied);
            }

            if (targetZone->IsFull())
            {
                if (m_addToStack)
                {
                    player.GetGame()->taskStack.entities = result;
                }

                return TaskStatus::COMPLETE;
            }
        }
    }

    if (m_addToStack)
    {
        player.GetGame()->taskStack.entities = result;
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
