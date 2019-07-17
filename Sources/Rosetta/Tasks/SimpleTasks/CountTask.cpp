// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
CountTask::CountTask(EntityType entityType, int numIndex)
    : ITask(entityType), m_numIndex(numIndex)
{
    // Do nothing
}

TaskID CountTask::GetTaskID() const
{
    return TaskID::COUNT;
}

TaskStatus CountTask::Impl(Player& player)
{
    const auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    const int count = static_cast<int>(entities.size());

    switch (m_numIndex)
    {
        case 0:
            player.GetGame()->taskStack.num = count;
            break;
        case 1:
            player.GetGame()->taskStack.num1 = count;
            break;
        default:
            throw std::invalid_argument(
                "CountTask::Impl() - Invalid number index");
    }
    return TaskStatus::COMPLETE;
}

ITask* CountTask::CloneImpl()
{
    return new CountTask(m_entityType, m_numIndex);
}
}  // namespace RosettaStone::SimpleTasks
