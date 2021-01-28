// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone::PlayMode
{
Aura::Aura(AuraType type, std::vector<std::shared_ptr<IEffect>> effects)
    : m_type(type), m_effects(std::move(effects))
{
    // Do nothing
}

Aura::Aura(AuraType type, std::string&& enchantmentID)
    : m_type(type), m_enchantmentCard(Cards::FindCardByID(enchantmentID))
{
    // Do nothing
}

AuraType Aura::GetType() const
{
    return m_type;
}

void Aura::Activate(Playable* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    auto instance = new Aura(*this, *owner);

    AddToGame(*owner, *instance);

    switch (removeTrigger.first)
    {
        case TriggerType::NONE:
            break;
        case TriggerType::TURN_END:
            owner->game->triggerManager.endTurnTrigger +=
                instance->m_removeHandler;
            break;
        case TriggerType::CAST_SPELL:
            owner->game->triggerManager.castSpellTrigger +=
                instance->m_removeHandler;
            break;
        case TriggerType::PLAY_MINION:
            owner->game->triggerManager.playMinionTrigger +=
                instance->m_removeHandler;
            break;
        case TriggerType::USE_HERO_POWER:
            owner->game->triggerManager.useHeroPowerTrigger +=
                instance->m_removeHandler;
            break;
        default:
            break;
    }

    if (!cloning && !restless)
    {
        instance->m_auraUpdateInstQueue.Push(
            AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
    }
}

void Aura::Update()
{
    bool addAllProcessed = false;

    if (restless)
    {
        RenewAll();
        addAllProcessed = true;
    }

    while (!m_auraUpdateInstQueue.IsEmpty())
    {
        const AuraUpdateInstruction inst = m_auraUpdateInstQueue.Pop();

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

void Aura::Remove()
{
    m_turnOn = false;
    m_auraUpdateInstQueue.Push(
        AuraUpdateInstruction(AuraInstruction::REMOVE_ALL), 0);
    m_owner->ongoingEffect = nullptr;

    switch (m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            EraseIf(m_owner->player->GetFieldZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::WEAPON:
        {
            EraseIf(m_owner->player->GetHero()->weaponAuras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::HAND:
        {
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::ENEMY_HAND:
        {
            EraseIf(m_owner->player->opponent->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::HANDS:
        {
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            EraseIf(m_owner->player->opponent->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::FIELD_AND_HAND:
        {
            EraseIf(m_owner->player->GetFieldZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        default:
        {
            // Do nothing
        }
    }

    switch (removeTrigger.first)
    {
        case TriggerType::NONE:
            break;
        case TriggerType::TURN_END:
            m_owner->game->triggerManager.endTurnTrigger -= m_removeHandler;
            break;
        case TriggerType::CAST_SPELL:
            m_owner->game->triggerManager.castSpellTrigger -= m_removeHandler;
            break;
        case TriggerType::USE_HERO_POWER:
            m_owner->game->triggerManager.useHeroPowerTrigger -=
                m_removeHandler;
            break;
        default:
            break;
    }

    if (auto enchantment = dynamic_cast<Enchantment*>(m_owner))
    {
        enchantment->Remove();
    }
}

void Aura::Clone(Playable* clone)
{
    Activate(clone, true);
}

void Aura::Apply(Playable* entity)
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
            Enchantment::GetInstance(entity->player, m_enchantmentCard, entity);

        if (auto trigger = m_enchantmentCard->power.GetTrigger();
            trigger != nullptr)
        {
            trigger->Activate(instance.get());
        }
    }

    m_appliedEntities.emplace_back(entity);
}

void Aura::Disapply(Playable* entity)
{
    const auto iter =
        std::find(m_appliedEntities.begin(), m_appliedEntities.end(), entity);

    if (iter != m_appliedEntities.end())
    {
        m_appliedEntities.erase(iter);
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
        auto enchantments = entity->appliedEnchantments;

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

void Aura::NotifyEntityAdded(Playable* entity)
{
    if (!m_turnOn)
    {
        return;
    }

    const auto instruction =
        AuraUpdateInstruction(entity, AuraInstruction::ADD);

    if (!m_auraUpdateInstQueue.IsExist(instruction))
    {
        m_auraUpdateInstQueue.Push(instruction, 2);
    }
}

void Aura::NotifyEntityRemoved(Playable* entity)
{
    if (!m_turnOn)
    {
        return;
    }

    if (entity == m_owner)
    {
        return;
    }

    m_auraUpdateInstQueue.Push(
        AuraUpdateInstruction(entity, AuraInstruction::REMOVE), 1);
}

Aura::Aura(Aura& prototype, Playable& owner)
    : condition(prototype.condition),
      removeTrigger(prototype.removeTrigger),
      restless(prototype.restless),
      m_type(prototype.m_type),
      m_owner(&owner),
      m_enchantmentCard(prototype.m_enchantmentCard),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn)
{
    if (!prototype.m_auraUpdateInstQueue.IsEmpty())
    {
        m_auraUpdateInstQueue = prototype.m_auraUpdateInstQueue;
    }

    auto removeFunc = [this](Entity* source) {
        if (removeTrigger.second != nullptr)
        {
            if (dynamic_cast<Player*>(source))
            {
                source = m_owner;
            }

            if (!removeTrigger.second->Evaluate(
                    dynamic_cast<Playable*>(source)))
            {
                return;
            }
        }

        Remove();
    };

    m_removeHandler = TriggerEventHandler(removeFunc);
}

void Aura::AddToGame(Playable& owner, Aura& aura)
{
    owner.game->auras.emplace_back(&aura);
    owner.ongoingEffect = &aura;

    switch (aura.m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
            owner.player->GetFieldZone()->auras.emplace_back(&aura);
            break;
        case AuraType::WEAPON:
            owner.player->GetHero()->weaponAuras.emplace_back(&aura);
            break;
        case AuraType::HAND:
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::ENEMY_HAND:
            owner.player->opponent->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::HANDS:
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            owner.player->opponent->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::FIELD_AND_HAND:
            owner.player->GetFieldZone()->auras.emplace_back(&aura);
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            break;
        default:
            break;
    }
}

void Aura::UpdateInternal()
{
    if (!m_turnOn)
    {
        return;
    }

    switch (m_type)
    {
        case AuraType::ADJACENT:
        {
            auto& field = *m_owner->player->GetFieldZone();
            if (field.GetCount() == 1)
            {
                return;
            }

            const int pos = m_owner->GetZonePosition();
            if (pos > 0)
            {
                Apply(field[pos - 1]);
            }
            if (pos < m_owner->player->GetFieldZone()->GetCount() - 1)
            {
                Apply(field[pos + 1]);
            }

            break;
        }
        case AuraType::FIELD:
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                Apply(minion);
            }
            break;
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                if (minion != m_owner)
                {
                    Apply(minion);
                }
            }
            break;
        }
        case AuraType::HERO_POWER:
        {
            Apply(m_owner->player->GetHero()->heroPower);
            break;
        }
        case AuraType::ENEMY_HERO_POWER:
        {
            Apply(m_owner->player->opponent->GetHero()->heroPower);
            break;
        }
        case AuraType::WEAPON:
        {
            if (m_owner->player->GetHero()->HasWeapon())
            {
                Apply(m_owner->player->GetHero()->weapon);
            }
            break;
        }
        case AuraType::HAND:
        {
            for (auto& card : m_owner->player->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            break;
        }
        case AuraType::ENEMY_HAND:
        {
            for (auto& card :
                 m_owner->player->opponent->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            break;
        }
        case AuraType::HANDS:
        {
            for (auto& card : m_owner->player->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            for (auto& card :
                 m_owner->player->opponent->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            break;
        }
        case AuraType::FIELD_AND_HAND:
        {
            for (auto& card : m_owner->player->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                Apply(minion);
            }
            break;
        }
        case AuraType::PLAYER:
        {
            for (auto& effect : m_effects)
            {
                const auto effectPtr = dynamic_cast<Effect*>(effect.get());
                effectPtr->ApplyTo(m_owner->player->playerAuraEffects);

                // NOTE: Living Dragonbreath (DRG_068)
                // When you summon this minion, it also unfreezes all friendly
                // minions that were frozen previously.
                if (effectPtr->GetGameTag() == GameTag::CANT_BE_FROZEN)
                {
                    if (auto hero = m_owner->player->GetHero();
                        hero->IsFrozen())
                    {
                        hero->SetGameTag(GameTag::FROZEN, 0);
                    }

                    for (auto& minion :
                         m_owner->player->GetFieldZone()->GetAll())
                    {
                        if (minion->IsFrozen())
                        {
                            minion->SetGameTag(GameTag::FROZEN, 0);
                        }
                    }
                }
                else if (effectPtr->GetGameTag() == GameTag::MEGA_WINDFURY)
                {
                    for (auto& minion :
                         m_owner->player->GetFieldZone()->GetAll())
                    {
                        // A minion can't attack at first turn in play.
                        if (minion->GetNumAttacksThisTurn() == 0 &&
                            minion->IsExhausted() == true)
                        {
                            break;
                        }

                        // A minion can't attack if it already attacked four
                        // times by having 'GameTag::MEGA_WINDFURY'.
                        if (minion->GetNumAttacksThisTurn() >= 4)
                        {
                            break;
                        }

                        minion->SetExhausted(false);
                    }
                }
            }
            break;
        }
        case AuraType::ENEMY_PLAYER:
        {
            for (auto& effect : m_effects)
            {
                const auto effectPtr = dynamic_cast<Effect*>(effect.get());
                effectPtr->ApplyTo(
                    m_owner->player->opponent->playerAuraEffects);
            }
            break;
        }
        case AuraType::PLAYERS:
        {
            for (auto& effect : m_effects)
            {
                const auto effectPtr = dynamic_cast<Effect*>(effect.get());
                effectPtr->ApplyTo(m_owner->player->playerAuraEffects);
                effectPtr->ApplyTo(
                    m_owner->player->opponent->playerAuraEffects);
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "Aura::UpdateInternal() - Invalid aura type!");
    }
}

void Aura::RemoveInternal()
{
    if (m_type == AuraType::PLAYER)
    {
        for (auto& effect : m_effects)
        {
            const auto effectPtr = dynamic_cast<Effect*>(effect.get());
            effectPtr->RemoveFrom(m_owner->player->playerAuraEffects);
        }
    }
    else if (m_type == AuraType::ENEMY_PLAYER)
    {
        for (auto& effect : m_effects)
        {
            const auto effectPtr = dynamic_cast<Effect*>(effect.get());
            effectPtr->RemoveFrom(m_owner->player->opponent->playerAuraEffects);
        }
    }
    else if (m_type == AuraType::PLAYERS)
    {
        for (auto& effect : m_effects)
        {
            const auto effectPtr = dynamic_cast<Effect*>(effect.get());
            effectPtr->RemoveFrom(m_owner->player->playerAuraEffects);
            effectPtr->RemoveFrom(m_owner->player->opponent->playerAuraEffects);
        }
    }
    else
    {
        for (auto& entity : m_appliedEntities)
        {
            for (auto& effect : m_effects)
            {
                effect->RemoveAuraFrom(entity);
            }
        }
    }

    EraseIf(m_owner->game->auras, [this](IAura* aura) { return aura == this; });

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        for (auto& entity : m_appliedEntities)
        {
            auto enchantments = entity->appliedEnchantments;

            for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
            {
                enchantments.erase(enchantments.begin() + i);
            }
        }
    }
}

void Aura::RenewAll()
{
    auto Renew = [this](Playable* playable) {
        const auto iter = std::find(m_appliedEntities.begin(),
                                    m_appliedEntities.end(), playable);

        if (condition->Evaluate(playable))
        {
            if (iter == m_appliedEntities.end())
            {
                Apply(playable);
            }
        }
        else
        {
            if (iter != m_appliedEntities.end())
            {
                Disapply(playable);
            }
        }
    };

    switch (m_type)
    {
        case AuraType::FIELD:
            m_owner->player->GetFieldZone()->ForEach(Renew);
            break;
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                if (minion != m_owner)
                {
                    Renew(minion);
                }
            }
            break;
        }
        case AuraType::HANDS:
            m_owner->player->GetHandZone()->ForEach(Renew);
            m_owner->player->opponent->GetHandZone()->ForEach(Renew);
            break;
        case AuraType::WEAPON:
            if (!m_owner->player->GetHero()->HasWeapon())
            {
                break;
            }
            Renew(m_owner->player->GetHero()->weapon);
            break;
        case AuraType::HERO:
            Renew(m_owner->player->GetHero());
            break;
        case AuraType::SELF:
            Renew(m_owner);
            break;
        default:
            throw std::invalid_argument(
                "Aura::RenewAll() - Invalid aura type!");
    }
}
}  // namespace RosettaStone::PlayMode
