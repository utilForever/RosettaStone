// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/SwitchingAura.hpp>
#include <Rosetta/Cards/Card.hpp>

#include <utility>
#include "Rosetta/Games/Game.hpp"
#include "Rosetta/Models/Entity.hpp"
#include "Rosetta/Models/Player.hpp"

namespace RosettaStone
{
SwitchingAura::SwitchingAura(AuraType type, SelfCondition initCondition,
                             TriggerType offTrigger,
                             std::vector<IEffect*> effects)
    : Aura(type, std::move(effects)),
      m_initCondition(std::move(initCondition)),
      m_offTrigger(offTrigger)
{
    // Do nothing
}

void SwitchingAura::Activate(Entity* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    auto instance = new SwitchingAura(*this, *owner);

    AddToGame(*owner, *instance);

    owner->owner->GetGame()->triggerManager.startTurnTrigger =
        instance->m_onHandler;
    owner->owner->GetGame()->triggerManager.endTurnTrigger =
        instance->m_offHandler;

    switch (m_offTrigger)
    {
        case TriggerType::PLAY_MINION:
            owner->owner->GetGame()->triggerManager.playMinionTrigger =
                instance->m_offHandler;
            break;
        case TriggerType::CAST_SPELL:
            owner->owner->GetGame()->triggerManager.castSpellTrigger =
                instance->m_offHandler;
            break;
        default:
            throw std::invalid_argument(
                "SwitchingAura::Activate() - Invalid trigger type!");
    }
}

SwitchingAura::SwitchingAura(SwitchingAura& prototype, Entity& owner)
    : Aura(prototype, owner),
      m_initCondition(prototype.m_initCondition),
      m_offTrigger(prototype.m_offTrigger)
{
    // Do nothing
}
}  // namespace RosettaStone
