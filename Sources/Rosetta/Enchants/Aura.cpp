// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Aura.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Player.hpp>

#include <algorithm>

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
      m_owner(&owner),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn)
{
    // Do nothing
}

void Aura::Activate(Entity& owner)
{
    if (m_effects.empty())
    {
        Card card = Cards::FindCardByID(m_enchantmentID);
        m_effects = card.power.GetEnchant().value().effects;
    }

    Aura* instance = new Aura(*this, owner);

    owner.GetOwner().GetGame()->auras.emplace_back(instance);
    owner.onGoingEffect = instance;

    instance->AddToField();
}

void Aura::Update()
{
    if (!m_toBeUpdated)
    {
        return;
    }

    UpdateInternal();
}

void Aura::Remove()
{
    m_turnOn = false;
    m_toBeUpdated = true;
    m_owner->onGoingEffect = nullptr;
}

void Aura::RemoveEntity(Entity& entity)
{
    if (&entity == m_owner)
    {
        Remove();
    }
    else
    {
        const auto iter = std::find(m_appliedEntities.begin(),
                              m_appliedEntities.end(), &entity);
        m_appliedEntities.erase(iter);
    }
}

void Aura::Apply(Entity& entity)
{
    for (auto& effect : m_effects)
    {
        effect.Apply(*entity.auraEffects);
    }

    m_appliedEntities.emplace_back(&entity);
}

void Aura::AddToField()
{
    switch (m_type)
    {
        case AuraType::FIELD_EXCEPT_SOURCE:
            m_owner->GetOwner().GetField().auras.emplace_back(this);
            break;
        default:
            throw std::invalid_argument(
                "Aura::AddToField() - Invalid aura type!");
    }
}

void Aura::UpdateInternal()
{
    if (m_turnOn)
    {
        switch (m_type)
        {
            case AuraType::FIELD_EXCEPT_SOURCE:
            {
                for (auto& minion :
                     m_owner->GetOwner().GetField().GetAllMinions())
                {
                    if (minion != m_owner)
                    {
                        Apply(*minion);
                    }
                }
                break;
            }
            default:
                throw std::invalid_argument(
                    "Aura::UpdateInternal() - Invalid aura type!");
        }

        m_toBeUpdated = false;
    }
    else
    {
        RemoveInternal();
    }
}

void Aura::RemoveInternal()
{
    switch (m_type)
    {
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            auto auras = m_owner->GetOwner().GetField().auras;
            const auto iter = std::find(auras.begin(), auras.end(), this);
            auras.erase(iter);
            break;
        }
        default:
            throw std::invalid_argument(
                "Aura::RemoveInternal() - Invalid aura type!");
    }

    for (auto& entity : m_appliedEntities)
    {
        for (auto& effect : m_effects)
        {
            effect.Remove(*entity->auraEffects);
        }
    }

    auto auras = m_owner->GetOwner().GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}
}  // namespace RosettaStone
