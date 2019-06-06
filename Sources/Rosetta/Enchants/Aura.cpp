// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Aura.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone
{
Aura::Aura(AuraType type, std::vector<Effect*> effects)
    : m_type(type), m_effects(std::move(effects))
{
    // Do nothing
}

Aura::Aura(AuraType type, std::string&& enchantmentID)
    : m_type(type), m_enchantmentID(enchantmentID)
{
    // Do nothing
}

void Aura::SetToBeUpdated(bool value)
{
    m_toBeUpdated = value;
}

void Aura::Activate(Entity* owner)
{
    Card card = Cards::FindCardByID(m_enchantmentID);

    if (m_effects.empty())
    {
        m_effects = card.power.GetEnchant()->effects;
    }

    auto instance = new Aura(*this, *owner);

    owner->owner->GetGame()->auras.emplace_back(instance);
    owner->onGoingEffect = instance;

    instance->AddToField();

    switch (m_type)
    {
        case AuraType::FIELD:
        {
            for (auto& minion : owner->owner->GetFieldZone().GetAll())
            {
                if (condition == nullptr || condition->Evaluate(minion))
                {
                    if (card.power.GetTrigger())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner->owner, card, minion);
                        card.power.GetTrigger()->Activate(enchantment);
                    }
                }

                instance->m_tempList.emplace_back(minion);
            }
            break;
        }
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : owner->owner->GetFieldZone().GetAll())
            {
                if (minion == owner)
                {
                    continue;
                }

                if (condition == nullptr || condition->Evaluate(minion))
                {
                    if (card.power.GetTrigger())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner->owner, card, minion);
                        card.power.GetTrigger()->Activate(enchantment);
                    }
                }

                instance->m_tempList.emplace_back(minion);
            }
            break;
        }
        default:
            break;
    }
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

void Aura::RemoveEntity(Entity* entity)
{
    if (entity == m_owner)
    {
        Remove();
    }
    else
    {
        if (m_appliedEntities.empty())
        {
            return;
        }
        const auto iter = std::find(m_appliedEntities.cbegin(),
                                    m_appliedEntities.cend(), entity);
        if (iter != m_appliedEntities.end())
        {
            m_appliedEntities.erase(iter);
        }
    }
}

void Aura::Apply(Entity* entity)
{
    const auto iter =
        std::find(m_appliedEntities.begin(), m_appliedEntities.end(), entity);
    if (iter != m_appliedEntities.end())
    {
        if (!restless || (condition != nullptr && condition->Evaluate(entity)))
        {
            return;
        }

        for (auto& effect : m_effects)
        {
            effect->Remove(*entity->auraEffects);
        }

        m_appliedEntities.erase(iter);
    }

    if (condition != nullptr && !condition->Evaluate(entity))
    {
        return;
    }

    for (auto& effect : m_effects)
    {
        effect->Apply(*entity->auraEffects);
    }

    m_appliedEntities.emplace_back(entity);
}

Aura::Aura(Aura& prototype, Entity& owner)
    : condition(prototype.condition),
      restless(prototype.restless),
      m_type(prototype.m_type),
      m_owner(&owner),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn),
      m_enchantmentID(prototype.m_enchantmentID)
{
    // Do nothing
}

void Aura::AddToField()
{
    switch (m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
            m_owner->owner->GetFieldZone().auras.emplace_back(this);
            break;
        case AuraType::HAND:
            m_owner->owner->GetHandZone().auras.emplace_back(this);
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
        if (!m_tempList.empty())
        {
            for (auto& temp : m_tempList)
            {
                Apply(temp);
            }

            m_tempList.clear();
        }

        switch (m_type)
        {
            case AuraType::ADJACENT:
            {
                const int pos = m_owner->GetZonePosition();
                auto& field = m_owner->owner->GetFieldZone();

                const int entitySize =
                    static_cast<int>(m_appliedEntities.size());
                for (int i = entitySize - 1; i >= 0; --i)
                {
                    Entity* entity = m_appliedEntities[i];

                    if (m_owner->zone == entity->zone &&
                        std::abs(pos - entity->GetZonePosition()) == 1)
                    {
                        continue;
                    }

                    for (auto& effect : m_effects)
                    {
                        effect->Remove(*entity->auraEffects);
                    }

                    auto iter = std::find(m_appliedEntities.begin(),
                                          m_appliedEntities.end(), entity);
                    if (iter != m_appliedEntities.end())
                    {
                        m_appliedEntities.erase(iter);
                    }
                }

                if (pos > 0)
                {
                    Apply(field[pos - 1]);
                }
                if (pos < m_owner->owner->GetFieldZone().GetCount() - 1 &&
                    m_owner->owner->GetFieldZone().GetCount() > pos)
                {
                    Apply(field[pos + 1]);
                }

                break;
            }
            case AuraType::FIELD:
                for (auto& minion : m_owner->owner->GetFieldZone().GetAll())
                {
                    Apply(minion);
                }
                break;
            case AuraType::FIELD_EXCEPT_SOURCE:
            {
                for (auto& minion : m_owner->owner->GetFieldZone().GetAll())
                {
                    if (minion != m_owner)
                    {
                        Apply(minion);
                    }
                }
                break;
            }
            case AuraType::HAND:
            {
                for (auto& card : m_owner->owner->GetHandZone().GetAll())
                {
                    Apply(card);
                }
                break;
            }
            default:
                throw std::invalid_argument(
                    "Aura::UpdateInternal() - Invalid aura type!");
        }

        if (!restless)
        {
            m_toBeUpdated = false;
        }
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
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            EraseIf(m_owner->owner->GetFieldZone().auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::HAND:
        {
            EraseIf(m_owner->owner->GetHandZone().auras,
                    [this](Aura* aura) { return aura == this; });
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
            effect->Remove(*entity->auraEffects);
        }
    }

    auto auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}

AuraType Aura::GetAuraType() const
{
    return m_type;
}

std::vector<Effect*> Aura::GetEffects() const
{
    return m_effects;
}

std::vector<Entity*> Aura::GetAppliedEntities() const
{
    return m_appliedEntities;
}

AdaptiveEffect::AdaptiveEffect(SelfCondition* _condition,
                               std::vector<GameTag> tags)
    : Aura(AuraType::ADAPTIVE, std::vector<Effect*>{}),
      m_tags(std::move(tags)),
      m_lastValues(std::vector(m_tags.size(), 0)),
      m_isSwitching(true)
{
    condition = _condition;
}

void AdaptiveEffect::Activate(Entity* owner)
{
    auto instance = new AdaptiveEffect(*this, *owner);

    owner->owner->GetGame()->auras.emplace_back(instance);
    owner->onGoingEffect = instance;
}

void AdaptiveEffect::Update()
{
    if (m_isSwitching)
    {
        for (std::size_t i = 0; i < m_tags.size(); ++i)
        {
            const int val = condition->Evaluate(m_owner) ? 1 : 0;
            if (m_lastValues[i] == val)
            {
                continue;
            }

            Effect(m_tags[i], EffectOperator::SET, val).Apply(m_owner);
            m_lastValues[i] = val;
        }
    }
}

void AdaptiveEffect::Remove()
{
    m_owner->onGoingEffect = nullptr;
    auto& auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}

AdaptiveEffect::AdaptiveEffect(AdaptiveEffect& prototype, Entity& owner)
    : Aura(prototype, owner)
{
    if (prototype.m_isSwitching)
    {
        condition = prototype.condition;
        m_tags = prototype.m_tags;
        m_lastValues = prototype.m_lastValues;
        m_isSwitching = true;

        return;
    }
}

EnrageEffect::EnrageEffect(AuraType type, std::vector<Effect*> effects)
    : Aura(type, std::move(effects))
{
    // Do nothing
}

void EnrageEffect::Activate(Entity* owner)
{
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
    auto minion = dynamic_cast<Minion*>(m_owner);

    if (m_type == AuraType::WEAPON)
    {
        m_target = minion->owner->GetHero()->weapon;
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
            m_target = owner.owner->GetHero()->weapon;
            break;
        default:
            break;
    }
}
}  // namespace RosettaStone
