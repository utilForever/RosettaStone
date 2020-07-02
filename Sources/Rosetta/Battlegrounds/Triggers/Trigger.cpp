// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>

#include <utility>

namespace RosettaStone::Battlegrounds
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    // Do nothing
}

Trigger::Trigger(Trigger& prototype, Minion& owner)
    : m_triggerType(prototype.m_triggerType),
      m_triggerActivation(prototype.m_triggerActivation),
      m_triggerSource(prototype.m_triggerSource),
      m_tasks(prototype.m_tasks),
      m_condition(prototype.m_condition)
{
    auto triggerFunc = [this](Minion& e) { Process(e); };
    handler = TriggerEventHandler(triggerFunc);
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

void Trigger::Activate(Player& player, Minion& source,
                       TriggerActivation activation, bool cloning)
{
    if (!cloning && activation != m_triggerActivation)
    {
        if (m_triggerActivation != TriggerActivation::HAND_OR_PLAY)
        {
            return;
        }
    }

    auto instance = Trigger(*this, source);
    source.activatedTrigger = std::move(instance);

    player.activateTriggerCallback(m_triggerType,
                                   source.activatedTrigger.handler);
}

void Trigger::Process(Minion& source)
{
}
}  // namespace RosettaStone::Battlegrounds
