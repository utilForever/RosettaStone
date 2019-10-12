// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathSubTask.hpp>

namespace RosettaStone::SimpleTasks
{
MathSubTask::MathSubTask(EntityType entityType, GameTag tag, int amount)
    : ITask(entityType), m_gameTag(tag), m_amount(amount)
{
    // Do nothing
}

MathSubTask::MathSubTask(EntityType entityType, GameTag tag)
    : ITask(entityType), m_gameTag(tag)
{
    // Do nothing
}

MathSubTask::MathSubTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus MathSubTask::Impl(Player& player)
{
    if (m_amount == 0)
    {
        auto entities =
            IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
        player.GetGame()->taskStack.num -= entities[0]->GetGameTag(m_gameTag);
    }
    else
    {
        player.GetGame()->taskStack.num -= m_amount;
    }

    return TaskStatus::COMPLETE;
}

ITask* MathSubTask::CloneImpl()
{
    return new MathSubTask(m_entityType, m_gameTag, m_amount);
}
}  // namespace RosettaStone::SimpleTasks
