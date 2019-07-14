// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <iostream>
namespace RosettaStone::SimpleTasks
{
CopyTask::CopyTask(EntityType entityType, int amount, bool isOpposite,
                   ZoneType zoneType)
    : ITask(entityType),
      m_amount(amount),
      m_isOpposite(isOpposite),
      m_zoneType(zoneType)
{
    // Do nothing
}

TaskID CopyTask::GetTaskID() const
{
    return TaskID::COPY;
}

TaskStatus CopyTask::Impl(Player& player)
{
    std::vector<Entity*> result;

    Player* owner = (m_isOpposite) ? player.opponent : &player;
    IZone* zone = Generic::GetZone(*owner, m_zoneType);

    auto entities = IncludeTask::GetEntities(m_entityType, *owner, m_source, m_target);

    if (entities.empty())
    {
        return TaskStatus::STOP;
    }

    if (zone != nullptr && zone->IsFull())
    {
        return TaskStatus::STOP;
    }

    if (m_amount < 1 || (m_amount != 1 && entities.size() != 1))
    {
        return TaskStatus::STOP;
    }

    for (int i = 0; i < m_amount; ++i)
    {
        for (auto& entity : entities)
        {
            Card card = 
                Cards::GetInstance().FindCardByID(entity->card.id);
            result.emplace_back(Entity::GetFromCard(
                player, std::move(card), std::nullopt, zone
            ));
        }
    }
    
    owner->GetGame()->taskStack.entities = result;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
