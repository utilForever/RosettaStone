// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

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

void Trigger::Validate(Minion& owner, Minion& source)
{
    Player& ownerPlayer = owner.getPlayerCallback();
    Player& sourcePlayer = source.getPlayerCallback();

    switch (m_triggerSource)
    {
        case TriggerSource::NONE:
            break;
        case TriggerSource::MINIONS_EXCEPT_SELF:
            if (ownerPlayer.idx != sourcePlayer.idx ||
                owner.GetIndex() == source.GetIndex())
            {
                return;
            }
            break;
        case TriggerSource::FRIENDLY:
            if (ownerPlayer.idx != sourcePlayer.idx)
            {
                return;
            }
            break;
        default:
            break;
    }

    switch (m_triggerType)
    {
        case TriggerType::SUMMON:
            if (owner.GetIndex() == source.GetIndex())
            {
                return;
            }
            break;
        default:
            break;
    }

    if (m_condition.has_value())
    {
        if (!m_condition.value().Evaluate(source))
        {
            return;
        }
    }

    m_isValidated = true;
}

void Trigger::Run(Minion& owner, Minion& source)
{
    Validate(owner, source);

    if (!m_isValidated)
    {
        return;
    }

    for (auto& task : m_tasks)
    {
        std::visit(
            [&](auto&& _task) { _task.Run(owner.getPlayerCallback(), owner); },
            task);
    }

    m_isValidated = false;
}
}  // namespace RosettaStone::Battlegrounds
