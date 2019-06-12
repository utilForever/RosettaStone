// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>

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

    switch (m_entityType)
    {
        case EntityType::TARGET:
        {
            if (m_target == nullptr)
            {
                return TaskStatus::STOP;
            }

            for (int i = 0; i < m_amount; ++i)
            {
                auto card =
                    Cards::GetInstance().FindCardByID(m_target->card.id);

                result.emplace_back(
                    m_isOpposite
                        ? Entity::GetFromCard(*m_target->owner->opponent,
                                              std::move(card))
                        : Entity::GetFromCard(player, std::move(card)));
            }
        }
        break;
        case EntityType::STACK:
        {
            IZone* zone = m_isOpposite
                              ? Generic::GetZone(*player.opponent, m_zoneType)
                              : Generic::GetZone(player, m_zoneType);

            for (auto& entity : player.GetGame()->taskStack.entities)
            {
                if (zone != nullptr && zone->IsFull())
                {
                    break;
                }

                for (int i = 0; i < m_amount; ++i)
                {
                    if (zone != nullptr && zone->IsFull())
                    {
                        break;
                    }

                    auto card =
                        Cards::GetInstance().FindCardByID(entity->card.id);

                    result.emplace_back(
                        m_isOpposite
                            ? Entity::GetFromCard(*player.opponent,
                                                  std::move(card), std::nullopt,
                                                  zone)
                            : Entity::GetFromCard(player, std::move(card),
                                                  std::nullopt, zone));
                }
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "CopyTask::Impl() - Invalid entity type");
    }

    player.GetGame()->taskStack.entities = result;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
