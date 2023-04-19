// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Auras/EnrageEffect.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

namespace RosettaStone::PlayMode
{
EnrageEffect::EnrageEffect(AuraType type, std::string&& enchantmentID)
    : Aura(type, std::move(enchantmentID))
{
    // Do nothing
}

void EnrageEffect::Activate(Playable* owner, [[maybe_unused]] bool cloning)
{
    auto instance = new EnrageEffect(*this, *owner);

    owner->game->auras.emplace_back(instance);
    owner->ongoingEffect = instance;
}

void EnrageEffect::Update()
{
    const auto minion = dynamic_cast<Minion*>(m_owner);

    if (!m_turnOn)
    {
        EraseIf(m_owner->game->auras,
                [this](const IAura* aura) { return aura == this; });

        if (!m_enraged)
        {
            return;
        }

        if (m_type == AuraType::WEAPON)
        {
            if (!minion->player->GetHero()->HasWeapon())
            {
                return;
            }

            if (m_target != &minion->player->GetWeapon())
            {
                return;
            }
        }

        for (const auto& effect :
             m_enchantmentCard->power.GetEnchant()->effects)
        {
            effect->RemoveFrom(m_target);
        }

        if (m_curInstance)
        {
            m_curInstance->Remove();
        }
    }

    if (m_type == AuraType::WEAPON)
    {
        if (!minion->player->GetHero()->HasWeapon())
        {
            return;
        }

        if (const auto weapon = &minion->player->GetWeapon(); weapon)
        {
            if (m_curInstance)
            {
                m_curInstance->Remove();
            }

            m_curInstance = nullptr;
            m_target = weapon;
        }
    }

    if (!m_enraged)
    {
        if (minion->GetDamage() == 0)
        {
            return;
        }

        Generic::AddEnchantment(m_enchantmentCard, minion, m_target, 0, 0);

        m_enraged = true;
    }
    else
    {
        if (minion->GetDamage() != 0)
        {
            return;
        }

        for (const auto& effect :
             m_enchantmentCard->power.GetEnchant()->effects)
        {
            effect->RemoveFrom(minion);
        }

        if (m_curInstance)
        {
            m_curInstance->Remove();
        }

        m_enraged = false;
    }
}

void EnrageEffect::Clone(Playable* clone)
{
    Activate(clone, true);
}

EnrageEffect::EnrageEffect(const EnrageEffect& prototype, Playable& owner)
    : Aura(prototype, owner), m_enraged(prototype.m_enraged)
{
    restless = true;

    if (m_type == AuraType::SELF)
    {
        m_target = &owner;
    }
    else if (m_type == AuraType::WEAPON)
    {
        m_target = &owner.player->GetWeapon();
    }
}
}  // namespace RosettaStone::PlayMode
