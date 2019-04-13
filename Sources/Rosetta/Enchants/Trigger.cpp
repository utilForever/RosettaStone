// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/Trigger.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/Tasks.hpp>

#include <stdexcept>

namespace RosettaStone
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    // Do nothing
}

Trigger::Trigger(Trigger& prototype, Entity& owner)
    : singleTask(prototype.singleTask),
      m_triggerType(prototype.m_triggerType),
      m_owner(&owner)
{
    // Do nothing
}

void Trigger::Activate(Entity& source)
{
    Trigger* instance = new Trigger(*this, source);
    Game* game = source.GetOwner().GetGame();

    source.activatedTrigger = instance;

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1);
            break;
        default:
            throw std::invalid_argument(
                "Trigger::Activate() - Invalid trigger type!");
    }
}

void Trigger::Remove()
{
    Game* game = m_owner->GetOwner().GetGame();

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
        {
            game->triggerManager.startTurnTrigger = nullptr;
            break;
        }
        default:
            throw std::invalid_argument(
                "Trigger::Remove() - Invalid trigger type!");
    }

    delete m_owner->activatedTrigger;
}

void Trigger::Process(Entity* source)
{
    ProcessInternal(source);
}

void Trigger::ProcessInternal(Entity* source)
{
    singleTask->SetSource(m_owner);

    if (source != nullptr)
    {
        singleTask->SetTarget(source);
    }
    else
    {
        auto enchantment = dynamic_cast<Enchantment*>(m_owner);
        if (enchantment != nullptr && enchantment->GetTarget() != nullptr)
        {
            singleTask->SetTarget(enchantment->GetTarget());
        }
        else
        {
            singleTask->SetTarget(nullptr);
        }
    }

    m_owner->GetOwner().GetGame()->taskQueue.push_back(singleTask);
}
}  // namespace RosettaStone
