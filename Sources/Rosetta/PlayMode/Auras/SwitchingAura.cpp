// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Auras/SwitchingAura.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>

#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode
{
SwitchingAura::SwitchingAura(AuraType type, SelfCondition activateCondition,
                             TriggerType offTrigger,
                             std::vector<std::shared_ptr<IEffect>> effects)
    : Aura(type, std::move(effects)),
      m_activateCondition(std::move(activateCondition)),
      m_offTrigger(offTrigger)
{
    // Do nothing
}

SwitchingAura::SwitchingAura(AuraType type, SelfCondition activateCondition,
                             TriggerType offTrigger,
                             std::string&& enchantmentID)
    : Aura(type, std::move(enchantmentID)),
      m_activateCondition(std::move(activateCondition)),
      m_offTrigger(offTrigger)
{
    // Do nothing
}

void SwitchingAura::Activate(Playable* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    const auto instance = new SwitchingAura(*this, *owner);

    AddToGame(*owner, *instance);

    owner->game->triggerManager.startTurnTrigger += instance->m_onHandler;
    owner->game->triggerManager.endTurnTrigger += instance->m_offHandler;

    if (m_offTrigger == TriggerType::PLAY_MINION)
    {
        owner->game->triggerManager.playMinionTrigger += instance->m_offHandler;
    }
    else if (m_offTrigger == TriggerType::CAST_SPELL)
    {
        owner->game->triggerManager.castSpellTrigger += instance->m_offHandler;
    }
    else
    {
        throw std::invalid_argument(
            "SwitchingAura::Activate() - Invalid trigger type!");
    }

    if (!cloning)
    {
        if (!instance->m_activateCondition.Evaluate(owner))
        {
            instance->m_turnOn = false;
        }
        else
        {
            instance->m_auraUpdateInstQueue.Push(
                AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
        }
    }
}

void SwitchingAura::Remove()
{
    Aura::Remove();

    m_isRemoved = true;

    m_owner->game->triggerManager.startTurnTrigger -= m_onHandler;
    m_owner->game->triggerManager.endTurnTrigger -= m_offHandler;

    if (m_offTrigger == TriggerType::PLAY_MINION)
    {
        m_owner->game->triggerManager.playMinionTrigger -= m_offHandler;
    }
    else if (m_offTrigger == TriggerType::CAST_SPELL)
    {
        m_owner->game->triggerManager.castSpellTrigger -= m_offHandler;
    }
    else
    {
        throw std::invalid_argument(
            "SwitchingAura::Remove() - Invalid trigger type!");
    }
}

void SwitchingAura::RemoveInternal()
{
    for (const auto& entity : m_appliedEntities)
    {
        for (const auto& effect : m_effects)
        {
            effect->RemoveAuraFrom(entity);
        }
    }

    m_appliedEntities.clear();

    if (m_isRemoved)
    {
        EraseIf(m_owner->game->auras,
                [this](const IAura* aura) { return aura == this; });
    }
}

SwitchingAura::SwitchingAura(const SwitchingAura& prototype, Playable& owner)
    : Aura(prototype, owner),
      m_activateCondition(prototype.m_activateCondition),
      m_offTrigger(prototype.m_offTrigger)
{
    auto onFunc = [this](Entity*) {
        if (m_turnOn)
        {
            return;
        }

        m_turnOn = true;

        m_auraUpdateInstQueue.Push(
            AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
    };

    auto offFunc = [this, &owner](Entity*) {
        if (!m_turnOn)
        {
            return;
        }

        if (m_activateCondition.Evaluate(&owner))
        {
            return;
        }

        m_turnOn = false;

        m_auraUpdateInstQueue.Push(
            AuraUpdateInstruction(AuraInstruction::REMOVE_ALL), 0);
    };

    m_onHandler = TriggerEventHandler(onFunc);
    m_offHandler = TriggerEventHandler(offFunc);
}
}  // namespace RosettaStone::PlayMode
