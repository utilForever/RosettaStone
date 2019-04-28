// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
SummonTask::SummonTask(std::string cardID, int num)
    : m_cardID(std::move(cardID)), m_num(num)
{
    // Do nothing
}

SummonTask::SummonTask(std::string cardID, SummonSide side)
    : m_cardID(std::move(cardID)), m_side(side)
{
    // Do nothing
}

TaskID SummonTask::GetTaskID() const
{
    return TaskID::SUMMON;
}

TaskStatus SummonTask::Impl(Player& player)
{
    (void)m_side;

    for (int i = 0; i < m_num; ++i)
    {
        if (player.GetField().IsFull())
        {
            return TaskStatus::STOP;
        }

        Card card = Cards::FindCardByID(m_cardID);
        Entity* summonEntity = Entity::GetFromCard(player, std::move(card));
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
            default:
                throw std::invalid_argument(
                    "SummonTask::Impl() - Invalid summon side");
        }

        Generic::Summon(player, summonMinion, summonPos);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
