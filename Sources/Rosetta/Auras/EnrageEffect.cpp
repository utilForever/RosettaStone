// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/EnrageEffect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>

#include <stdexcept>

namespace RosettaStone
{
EnrageEffect::EnrageEffect(AuraType type, std::vector<Effect*> effects)
    : Aura(type, std::move(effects))
{
    // Do nothing
}

void EnrageEffect::Activate(Entity* owner, [[maybe_unused]] bool cloning)
{
    if (owner == nullptr)
    {
        throw std::logic_error(
            "EnrageEffect::Activate() - Owner can't be nullptr.");
    }

    const auto enchantment = dynamic_cast<Enchantment*>(owner);
    if (enchantment)
    {
        owner = nullptr;
        owner = enchantment->GetTarget();
    }

    auto instance = new EnrageEffect(*this, *owner);
    owner->owner->GetGame()->auras.emplace_back(instance);
    owner->onGoingEffect = instance;
}

void EnrageEffect::Update()
{
    const auto minion = dynamic_cast<Minion*>(m_owner);

    if (m_type == AuraType::WEAPON)
    {
        m_target = &minion->owner->GetWeapon();
    }

    if (!m_turnOn)
    {
        EraseIf(m_owner->owner->GetGame()->auras,
                [this](IAura* aura) { return aura == this; });

        if (!m_enraged)
        {
            return;
        }

        if (m_target != nullptr)
        {
            for (auto& effect : m_effects)
            {
                effect->Remove(*m_target->auraEffects);
            }
        }
    }

    if (!m_enraged)
    {
        if (minion->GetDamage() == 0)
        {
            return;
        }

        if (m_target != nullptr)
        {
            for (auto& effect : m_effects)
            {
                effect->Apply(*m_target->auraEffects);
            }
        }

        m_enraged = true;
    }
    else
    {
        if (minion->GetDamage() != 0)
        {
            return;
        }

        if (m_target != nullptr)
        {
            for (auto& effect : m_effects)
            {
                effect->Remove(*m_target->auraEffects);
            }
        }

        m_enraged = false;
    }
}

void EnrageEffect::Clone(Entity* clone)
{
    Activate(clone, true);
}

EnrageEffect::EnrageEffect(EnrageEffect& prototype, Entity& owner)
    : Aura(prototype, owner)
{
    m_enraged = prototype.m_enraged;
    restless = true;

    switch (m_type)
    {
        case AuraType::SELF:
            m_target = &owner;
            break;
        case AuraType::WEAPON:
            m_target = &owner.owner->GetWeapon();
            break;
        default:
            break;
    }
}
}  // namespace RosettaStone
