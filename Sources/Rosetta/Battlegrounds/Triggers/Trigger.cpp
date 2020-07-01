// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>

#include <utility>

namespace RosettaStone::Battlegrounds
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    // Do nothing
}

void Trigger::SetTriggerSource(TriggerSource val)
{
    m_triggerSource = val;
}

void Trigger::SetTasks(std::vector<TaskType> tasks)
{
    m_tasks = std::move(tasks);
}

void Trigger::SetCondition(SelfCondition&& condition)
{
    m_condition = condition;
}
}  // namespace RosettaStone::Battlegrounds
