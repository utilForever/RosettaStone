// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone::SimpleTasks
{
SummonOpTask::SummonOpTask(std::optional<Card*> card, int amount)
    : m_card(card), m_amount(amount)
{
    // Do nothing
}

SummonOpTask::SummonOpTask(const std::string& cardID, int amount)
    : m_card(Cards::FindCardByID(cardID)), m_amount(amount)
{
    // Do nothing
}

TaskStatus SummonOpTask::Impl(Player* player)
{
    TaskStack stack = player->game->taskStack;

    if (!m_card.has_value() && stack.playables.empty())
    {
        return TaskStatus::STOP;
    }

    for (int i = 0; i < m_amount; ++i)
    {
        if (player->opponent->GetFieldZone()->IsFull())
        {
            return TaskStatus::STOP;
        }

        Minion* summonEntity;

        if (!m_card.has_value())
        {
            summonEntity = dynamic_cast<Minion*>(stack.playables[0]);
        }
        else
        {
            summonEntity = dynamic_cast<Minion*>(
                Entity::GetFromCard(player->opponent, m_card.value()));
        }

        Generic::Summon(summonEntity, -1, m_source);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonOpTask::CloneImpl()
{
    return std::make_unique<SummonOpTask>(m_card, m_amount);
}
}  // namespace RosettaStone::SimpleTasks
