// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>

namespace RosettaStone::SimpleTasks
{
FlagTask::FlagTask(bool flag, ITask* toDoTask)
    : m_flag(flag), m_toDoTask(toDoTask)
{
    // Do nothing
}

TaskID FlagTask::GetTaskID() const
{
    return TaskID::FLAG;
}

ITask* FlagTask::CloneImpl()
{
    return new FlagTask(m_flag, m_toDoTask);
}

TaskStatus FlagTask::Impl(Player& player)
{
    if (player.GetGame()->taskStack.flag != m_flag)
    {
        return TaskStatus::COMPLETE;
    }

    m_toDoTask->SetPlayer(&player);
    m_toDoTask->SetSource(player.GetGame()->taskStack.source);
    m_toDoTask->SetTarget(player.GetGame()->taskStack.target);

    return m_toDoTask->Run();
}
}  // namespace RosettaStone::SimpleTasks
