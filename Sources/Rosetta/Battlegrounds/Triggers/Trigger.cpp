// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>

namespace RosettaStone::Battlegrounds
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    // Do nothing
}

TriggerType Trigger::GetTriggerType() const
{
    return m_triggerType;
}

TriggerSource Trigger::GetTriggerSource() const
{
    return m_triggerSource;
}

void Trigger::SetTriggerSource(TriggerSource val)
{
    m_triggerSource = val;
}

void Trigger::SetTasks(std::vector<TaskType>&& tasks)
{
    m_tasks = tasks;
}

void Trigger::SetCondition(SelfCondition&& condition)
{
    m_condition = condition;
}

void Trigger::Run(Player& player, Minion& source)
{
    for (auto& task : m_tasks)
    {
        std::visit([&](auto&& _task) { _task.Run(player, source); }, task);
    }
}
}  // namespace RosettaStone::Battlegrounds
