// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Trigger.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    switch (type)
    {
        case TriggerType::PLAY_CARD:
            m_sequenceType = SequenceType::PLAY_CARD;
            break;
        case TriggerType::CAST_SPELL:
        case TriggerType::AFTER_CAST:
            m_sequenceType = SequenceType::PLAY_SPELL;
            break;
        case TriggerType::TARGET:
            m_sequenceType = SequenceType::TARGET;
            break;
        case TriggerType::TURN_END:
            fastExecution = true;
            break;
        default:
            m_sequenceType = SequenceType::NONE;
    }
}

Trigger::Trigger(Trigger& prototype, Entity& owner)
    : triggerSource(prototype.triggerSource),
      tasks(prototype.tasks),
      condition(prototype.condition),
      fastExecution(prototype.fastExecution),
      removeAfterTriggered(prototype.removeAfterTriggered),
      m_owner(&owner),
      m_triggerType(prototype.m_triggerType),
      m_triggerActivation(prototype.m_triggerActivation),
      m_sequenceType(prototype.m_sequenceType)
{
    // Do nothing
}

void Trigger::Activate(Entity* source, TriggerActivation activation,
                       bool cloning)
{
    if (!cloning && activation != m_triggerActivation)
    {
        if (m_triggerActivation != TriggerActivation::HAND_OR_PLAY)
        {
            return;
        }
    }

    auto* instance = new Trigger(*this, *source);
    Game* game = source->owner->GetGame();

    source->activatedTrigger = instance;

    auto triggerFunc = [instance](Player* p, Entity* e) {
        instance->Process(p, e);
    };

    if (m_sequenceType != SequenceType::NONE)
    {
        source->owner->GetGame()->triggers.emplace_back(instance);
    }

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger = std::move(triggerFunc);
            break;
        case TriggerType::TURN_END:
            game->triggerManager.endTurnTrigger = std::move(triggerFunc);
            break;
        case TriggerType::PLAY_CARD:
            game->triggerManager.playCardTrigger = std::move(triggerFunc);
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger = std::move(triggerFunc);
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger = std::move(triggerFunc);
            break;
        case TriggerType::HEAL:
            game->triggerManager.healTrigger = std::move(triggerFunc);
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger = std::move(triggerFunc);
            break;
        case TriggerType::AFTER_ATTACK:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->owner->GetHero()->afterAttackTrigger =
                        std::move(triggerFunc);
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(source);
                    minion->afterAttackTrigger = std::move(triggerFunc);
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->afterAttackTrigger = std::move(triggerFunc);
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger = std::move(triggerFunc);
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->owner->GetHero()->preDamageTrigger =
                        std::move(triggerFunc);
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(source);
                    minion->preDamageTrigger = std::move(triggerFunc);
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->preDamageTrigger = std::move(triggerFunc);
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger = std::move(triggerFunc);
            break;
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger = std::move(triggerFunc);
            break;
        default:
            break;
    }
}

void Trigger::Remove() const
{
    Game* game = m_owner->owner->GetGame();

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger = nullptr;
            break;
        case TriggerType::TURN_END:
            game->triggerManager.endTurnTrigger = nullptr;
            break;
        case TriggerType::PLAY_CARD:
            game->triggerManager.playCardTrigger = nullptr;
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger = nullptr;
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger = nullptr;
            break;
        case TriggerType::HEAL:
            game->triggerManager.healTrigger = nullptr;
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger = nullptr;
            break;
        case TriggerType::AFTER_ATTACK:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->owner->GetHero()->afterAttackTrigger = nullptr;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->afterAttackTrigger = nullptr;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->afterAttackTrigger = nullptr;
                    break;
                }
                default:
                    break;
            }
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger = nullptr;
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->owner->GetHero()->preDamageTrigger = nullptr;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->preDamageTrigger = nullptr;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->preDamageTrigger = nullptr;
                    break;
                }
                default:
                    break;
            }
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger = nullptr;
            break;
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger = nullptr;
            break;
        default:
            break;
    }

    m_owner->activatedTrigger = nullptr;

    if (m_sequenceType != SequenceType::NONE)
    {
        EraseIf(game->triggers,
                [this](Trigger* trigger) { return trigger == this; });
    }
}

void Trigger::ValidateTriggers(Game* game, Entity* source, SequenceType type)
{
    for (auto& trigger : game->triggers)
    {
        if (trigger->m_sequenceType == type)
        {
            trigger->Validate(&game->GetCurrentPlayer(), source);
        }
    }
}

void Trigger::Process(Player* player, Entity* source)
{
    if (m_sequenceType == SequenceType::NONE)
    {
        Validate(player, source);
    }

    if (!m_isValidated)
    {
        return;
    }

    ProcessInternal(source);
}

void Trigger::ProcessInternal(Entity* source)
{
    m_isValidated = false;

    if (removeAfterTriggered)
    {
        Remove();
    }

    for (auto& task : tasks)
    {
        task->SetPlayer(m_owner->owner);
        task->SetSource(m_owner);

        if (source != nullptr)
        {
            task->SetTarget(source);
        }
        else
        {
            const auto enchantment = dynamic_cast<Enchantment*>(m_owner);
            if (enchantment != nullptr && enchantment->GetTarget() != nullptr)
            {
                task->SetTarget(enchantment->GetTarget());
            }
            else
            {
                task->SetTarget(nullptr);
            }
        }

        if (fastExecution)
        {
            task->Run();
        }
        else
        {
            m_owner->owner->GetGame()->taskQueue.Enqueue(task);
        }
    }

    m_isValidated = false;
}

void Trigger::Validate(Player* player, Entity* source)
{
    switch (triggerSource)
    {
        case TriggerSource::NONE:
            break;
        case TriggerSource::SELF:
            if (source != m_owner)
            {
                return;
            }
            break;
        case TriggerSource::HERO:
            if (dynamic_cast<Hero*>(source) == nullptr ||
                source->owner != m_owner->owner)
            {
                return;
            }
            break;
        case TriggerSource::ALL_MINIONS:
            if (dynamic_cast<Minion*>(source) == nullptr)
            {
                return;
            }
            break;
        case TriggerSource::MINIONS_EXCEPT_SELF:
            if (dynamic_cast<Minion*>(source) == nullptr ||
                source->owner != m_owner->owner || source == m_owner)
            {
                return;
            }
            break;
        case TriggerSource::ENCHANTMENT_TARGET:
        {
            const auto enchantment = dynamic_cast<Enchantment*>(m_owner);
            if (enchantment == nullptr ||
                enchantment->GetTarget()->id != source->id)
            {
                return;
            }
            break;
        }
        case TriggerSource::FRIENDLY:
        {
            if (source->owner != m_owner->owner)
            {
                return;
            }
            break;
        }
        default:
            break;
    }

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
        case TriggerType::TURN_END:
            if (player != m_owner->owner)
            {
                return;
            }
            break;
        case TriggerType::PLAY_CARD:
        case TriggerType::SUMMON:
            if (source == m_owner)
            {
                return;
            }
            break;
        default:
            break;
    }

    if (condition != nullptr)
    {
        const bool res = (source != nullptr) ? condition->Evaluate(source)
                                             : condition->Evaluate(m_owner);

        if (!res)
        {
            return;
        }
    }

    m_isValidated = true;
}
}  // namespace RosettaStone
