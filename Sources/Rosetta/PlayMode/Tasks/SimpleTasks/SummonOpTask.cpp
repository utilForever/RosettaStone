// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SummonOpTask::SummonOpTask(std::optional<Card*> card, int amount,
                           SummonSide side)
    : m_card(card), m_amount(amount), m_side(side)
{
    // Do nothing
}

SummonOpTask::SummonOpTask(const std::string& cardID, int amount,
                           SummonSide side)
    : m_card(Cards::FindCardByID(cardID)), m_amount(amount), m_side(side)
{
    // Do nothing
}

TaskStatus SummonOpTask::Impl(Player* player)
{
    const TaskStack stack = player->game->taskStack;

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
        int alternateCount = 0;

        if (!m_card.has_value())
        {
            summonEntity = dynamic_cast<Minion*>(stack.playables[0]);
        }
        else
        {
            summonEntity = dynamic_cast<Minion*>(
                Entity::GetFromCard(player->opponent, m_card.value()));
        }

        const int pos =
            SummonTask::GetPosition(m_source, m_side, m_target, alternateCount);
        const int summonPos =
            std::min(pos, player->opponent->GetFieldZone()->GetCount());

        if (summonEntity->IsUntouchable())
        {
            player->opponent->GetFieldZone()->Add(summonEntity, summonPos);
        }
        else
        {
            Generic::Summon(summonEntity, summonPos, m_source);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonOpTask::CloneImpl()
{
    return std::make_unique<SummonOpTask>(m_card, m_amount, m_side);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
