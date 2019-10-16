// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/Aura.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone
{
Aura::Aura(AuraType type, std::vector<IEffect*> effects)
    : m_type(type), m_effects(std::move(effects))
{
    // Do nothing
}

Aura::Aura(AuraType type, std::string&& enchantmentID)
    : m_type(type), m_enchantmentCard(Cards::FindCardByID(enchantmentID))
{
    // Do nothing
}

void Aura::Update()
{
    bool addAllProcessed = false;

    if (restless)
    {
        RenewAll();
        addAllProcessed = true;
    }

    while (!m_auraUpdateInstQueue.empty())
    {
        const AuraUpdateInstruction inst = m_auraUpdateInstQueue.top();
        m_auraUpdateInstQueue.pop();

        switch (inst.instruction)
        {
            case AuraInstruction::ADD:
                if (!addAllProcessed)
                {
                    Apply(inst.source);
                }
                break;
            case AuraInstruction::ADD_ALL:
                addAllProcessed = true;
                UpdateInternal();
                break;
            case AuraInstruction::REMOVE:
                Disapply(inst.source);
                break;
            case AuraInstruction::REMOVE_ALL:
                RemoveInternal();
                break;
            default:
                throw std::invalid_argument(
                    "Aura::Update() - Invalid aura instruction!");
        }
    }
}

void Aura::Activate(Entity* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    auto instance = new Aura(*this, *owner);

    AddToGame(*owner, *instance);

    owner->owner->GetGame()->auras.emplace_back(instance);
    owner->onGoingEffect = instance;

    if (!cloning)
    {
        instance->AddToField();
    }

    if (cloning)
    {
        return;
    }

    switch (m_type)
    {
        case AuraType::FIELD:
        {
            for (auto& minion : owner->owner->GetFieldZone().GetAll())
            {
                if (condition == nullptr || condition->Evaluate(minion))
                {
                    if (card->power.GetTrigger())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner->owner, card, minion);
                        card->power.GetTrigger()->Activate(enchantment);
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
                    if (card->power.GetTrigger())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner->owner, card, minion);
                        card->power.GetTrigger()->Activate(enchantment);
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

void Aura::Clone(Entity* clone)
{
    Activate(clone, true);
    dynamic_cast<Aura*>(clone->onGoingEffect)->SetToBeUpdated(m_toBeUpdated);
}

void Aura::Apply(Entity* entity)
{
    if (condition != nullptr)
    {
        if (!condition->Evaluate(entity))
        {
            return;
        }
    }

    for (auto& effect : m_effects)
    {
        effect->ApplyAuraTo(entity);
    }

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        const auto instance =
            Enchantment::GetInstance(*entity->owner, m_enchantmentCard, entity);

        if (auto trigger = m_enchantmentCard->power.GetTrigger();
            trigger != nullptr)
        {
            trigger->Activate(instance);
        }
    }

    m_appliedEntityIDs.emplace_back(entity->id);
}

void Aura::Disapply(Entity* entity)
{
    const auto iter = std::find(m_appliedEntityIDs.begin(),
                                m_appliedEntityIDs.end(), entity->id);

    if (iter != m_appliedEntityIDs.end())
    {
        m_appliedEntityIDs.erase(iter);
    }
    else
    {
        return;
    }

    for (auto& effect : m_effects)
    {
        effect->RemoveAuraFrom(entity);
    }

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        const std::string cardID = m_enchantmentCard->id;
        std::vector<Enchantment*> enchantments = entity->appliedEnchantments;

        for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
        {
            if (enchantments[i]->card->id == cardID)
            {
                enchantments.erase(enchantments.begin() + i);
                break;
            }
        }
    }
}

Aura::Aura(Aura& prototype, Entity& owner)
    : condition(prototype.condition),
      restless(prototype.restless),
      m_type(prototype.m_type),
      m_owner(&owner),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn),
      m_enchantmentCard(prototype.m_enchantmentCard)
{
    if (!prototype.m_auraUpdateInstQueue.empty())
    {
        m_auraUpdateInstQueue = prototype.m_auraUpdateInstQueue;
    }
}

void Aura::AddToGame(Entity& owner, Aura& aura)
{
    owner.owner->GetGame()->auras.emplace_back(&aura);
    owner.onGoingEffect = &aura;

    switch (aura.GetAuraType())
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
            m_owner->owner->GetFieldZone().auras.emplace_back(this);
            break;
        case AuraType::HAND:
            m_owner->owner->GetHandZone().auras.emplace_back(this);
            break;
        case AuraType::ENEMY_HAND:
            m_owner->owner->opponent->GetHandZone().auras.emplace_back(this);
            break;
        case AuraType::HANDS:
            m_owner->owner->GetHandZone().auras.emplace_back(this);
            m_owner->owner->opponent->GetHandZone().auras.emplace_back(this);
            break;
        case AuraType::FIELD_AND_HAND:
            m_owner->owner->GetFieldZone().auras.emplace_back(this);
            m_owner->owner->GetHandZone().auras.emplace_back(this);
            break;
        default:
            throw std::invalid_argument(
                "Aura::AddToGame() - Invalid aura type!");
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

    auto& auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}

void Aura::RenewAll()
{
    auto Renew = [this](Entity* entity) {
        const auto iter = std::find(m_appliedEntityIDs.begin(),
                                    m_appliedEntityIDs.end(), entity->id);

        if (condition->Evaluate(entity))
        {
            if (iter == m_appliedEntityIDs.end())
            {
                Apply(entity);
            }
        }
        else
        {
            if (iter != m_appliedEntityIDs.end())
            {
                Disapply(entity);
            }
        }
    };

    switch (m_type)
    {
        case AuraType::FIELD:
            m_owner->owner->GetFieldZone().ForEach(Renew);
            break;
        case AuraType::HANDS:
            m_owner->owner->GetHandZone().ForEach(Renew);
            m_owner->owner->opponent->GetHandZone().ForEach(Renew);
            break;
        case AuraType::WEAPON:
            if (!m_owner->owner->GetHero()->HasWeapon())
            {
                break;
            }
            Renew(m_owner->owner->GetHero()->weapon);
            break;
        case AuraType::HERO:
            Renew(m_owner->owner->GetHero());
            break;
        case AuraType::SELF:
            Renew(m_owner);
            break;
        default:
            throw std::invalid_argument(
                "Aura::RenewAll() - Invalid aura type!");
    }
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
}  // namespace RosettaStone
