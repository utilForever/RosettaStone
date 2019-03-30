// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Aura.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Aura::Aura(std::string&& enchantmentID, AuraType type)
    : m_enchantmentID(enchantmentID), m_type(type)
{
    // Do nothing
}

Aura::Aura(Aura& prototype, Entity& owner)
    : m_enchantmentID(prototype.m_enchantmentID),
      m_type(prototype.m_type),
      m_owner(&owner)
{
    // Do nothing
}

void Aura::Activate(Entity& owner)
{
    if (m_effects.empty())
    {
        Card card = Cards::FindCardByID(m_enchantmentID);
        m_effects = card.power.GetEnchant().effects;
    }

    Aura* instance = new Aura(*this, owner);

    owner.GetOwner().GetGame()->auras.emplace_back(instance);

    switch (m_type)
    {
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            owner.GetOwner().GetField().AddAura(instance);
            break;
        }
    }
}

void Aura::Update()
{
    switch (m_type)
    {
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : m_owner->GetOwner().GetField().GetAllMinions())
            {
                if (minion != m_owner)
                {
                    Apply(minion);
                }
            }
        }
    }
}

void Aura::Apply(Character* character)
{
    for (auto& effect : m_effects)
    {
        effect.Apply(character->auraEffects);
    }
}
}  // namespace RosettaStone
