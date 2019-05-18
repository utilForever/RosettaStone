// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
SummonTask::SummonTask(SummonSide side, std::optional<Card> card, int amount)
    : m_card(std::move(card)), m_side(side), m_amount(amount)
{
    // Do nothing
}

SummonTask::SummonTask(std::string cardID, int amount) : m_amount(amount)
{
    m_card = Cards::FindCardByID(cardID);
}

SummonTask::SummonTask(std::string cardID, SummonSide side) : m_side(side)
{
    m_card = Cards::FindCardByID(cardID);
}

TaskID SummonTask::GetTaskID() const
{
    return TaskID::SUMMON;
}

TaskStatus SummonTask::Impl(Player& player)
{
    for (int i = 0; i < m_amount; ++i)
    {
        if (player.GetFieldZone().IsFull())
        {
            return TaskStatus::STOP;
        }

        Entity* summonEntity = nullptr;
        if (m_card.has_value())
        {
            summonEntity =
                Entity::GetFromCard(player, std::move(m_card.value()));
        }
        else if (!player.GetGame()->taskStack.entities.empty())
        {
            summonEntity = player.GetGame()->taskStack.entities[0];
        }

        if (summonEntity == nullptr)
        {
            return TaskStatus::STOP;
        }

        const auto summonMinion = dynamic_cast<Minion*>(summonEntity);
        if (summonMinion == nullptr)
        {
            return TaskStatus::STOP;
        }

        int summonPos;
        switch (m_side)
        {
            case SummonSide::DEFAULT:
                summonPos = -1;
                break;
            case SummonSide::RIGHT:
            {
                auto field = m_source->owner->GetFieldZone();
                const auto minion = dynamic_cast<Minion*>(m_source);
                const auto fieldPos = field.FindMinionPos(*minion);

                if (fieldPos.has_value())
                {
                    summonPos = static_cast<int>(fieldPos.value()) + 1;
                }
                else
                {
                    summonPos = -1;
                }
                break;
            }
            default:
                throw std::invalid_argument(
                    "SummonTask::Impl() - Invalid summon side");
        }

        Generic::Summon(player, summonMinion, summonPos);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
