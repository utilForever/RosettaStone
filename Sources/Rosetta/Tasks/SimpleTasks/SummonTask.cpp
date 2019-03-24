// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::SimpleTasks
{
SummonTask::SummonTask(std::string cardID, int num) : m_cardID(cardID), m_num(num)
{
    // Do nothing
}

TaskID SummonTask::GetTaskID() const
{
    return TaskID::SUMMON;
}

TaskStatus SummonTask::Impl(Player& player)
{
    for (int i = 0; i < m_num; ++i)
    {
        if (player.GetField().IsFull())
        {
            return TaskStatus::STOP;
        }

        Card card = Cards::GetInstance().FindCardByID(m_cardID);
        Entity* minion = Entity::GetFromCard(player, std::move(card));
        int fieldPos =
            static_cast<int>(player.GetField().FindEmptyPos().value());
        Generic::Summon(player, dynamic_cast<Minion*>(minion), fieldPos);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
