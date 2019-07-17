// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncEntityTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
FuncEntityTask::FuncEntityTask(
    std::function<std::vector<Entity*>(std::vector<Entity*>)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskID FuncEntityTask::GetTaskID() const
{
    return TaskID::FUNC_ENTITY;
}

TaskStatus FuncEntityTask::Impl(Player& player)
{
    if (m_func != nullptr)
    {
        player.GetGame()->taskStack.entities =
            m_func(player.GetGame()->taskStack.entities);
    }

    return TaskStatus::COMPLETE;
}

ITask* FuncEntityTask::CloneImpl()
{
    return new FuncEntityTask(m_func);
}
}  // namespace RosettaStone::SimpleTasks
