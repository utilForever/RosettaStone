// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Trigger.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Tasks/ITask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    switch (type)
    {
        case TriggerType::PLAY_CARD:
            m_sequenceType = SequenceType::PLAY_CARD;
            break;
        case TriggerType::PLAY_MINION:
        case TriggerType::AFTER_PLAY_MINION:
            m_sequenceType = SequenceType::PLAY_MINION;
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
      eitherTurn(prototype.eitherTurn),
      fastExecution(prototype.fastExecution),
      removeAfterTriggered(prototype.removeAfterTriggered),
      m_owner(dynamic_cast<Playable*>(&owner)),
      m_triggerType(prototype.m_triggerType),
      m_triggerActivation(prototype.m_triggerActivation),
      m_sequenceType(prototype.m_sequenceType)
{
    // Do nothing
}

void Trigger::Activate(Playable* source, TriggerActivation activation,
                       bool cloning)
{
    if (!cloning && activation != m_triggerActivation)
    {
        if (m_triggerActivation != TriggerActivation::HAND_OR_PLAY)
        {
            return;
        }
    }

    auto instance = std::make_shared<Trigger>(*this, *source);
    Game* game = source->game;

    source->activatedTrigger = instance;

    auto triggerFunc = [this, instance](Entity* e) {
        if (percentage == 1.0f || Random::get<float>(0.0f, 1.0f) < percentage)
        {
            instance->Process(e);
        }
    };

    if (m_sequenceType != SequenceType::NONE)
    {
        game->triggers.emplace_back(instance);
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
        case TriggerType::PLAY_MINION:
            game->triggerManager.playMinionTrigger = std::move(triggerFunc);
            break;
        case TriggerType::AFTER_PLAY_MINION:
            game->triggerManager.afterPlayMinionTrigger =
                std::move(triggerFunc);
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger = std::move(triggerFunc);
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger = std::move(triggerFunc);
            break;
        case TriggerType::SECRET_REVEALED:
            game->triggerManager.secretRevealedTrigger = std::move(triggerFunc);
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
                    source->player->GetHero()->afterAttackTrigger =
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
        case TriggerType::AFTER_SUMMON:
            game->triggerManager.afterSummonTrigger = std::move(triggerFunc);
            break;
        case TriggerType::DEAL_DAMAGE:
            game->triggerManager.dealDamageTrigger = std::move(triggerFunc);
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger = std::move(triggerFunc);
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->player->GetHero()->preDamageTrigger =
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
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger = std::move(triggerFunc);
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger = std::move(triggerFunc);
            break;
        case TriggerType::USE_HERO_POWER:
            game->triggerManager.useHeroPowerTrigger = std::move(triggerFunc);
            break;
        default:
            break;
    }
}

void Trigger::Remove() const
{
    Game* game = m_owner->game;

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
        case TriggerType::PLAY_MINION:
            game->triggerManager.playMinionTrigger = nullptr;
            break;
        case TriggerType::AFTER_PLAY_MINION:
            game->triggerManager.afterPlayMinionTrigger = nullptr;
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger = nullptr;
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger = nullptr;
            break;
        case TriggerType::SECRET_REVEALED:
            game->triggerManager.secretRevealedTrigger = nullptr;
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
                    m_owner->player->GetHero()->afterAttackTrigger = nullptr;
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
        case TriggerType::AFTER_SUMMON:
            game->triggerManager.afterSummonTrigger = nullptr;
            break;
        case TriggerType::DEAL_DAMAGE:
            game->triggerManager.dealDamageTrigger = nullptr;
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger = nullptr;
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->player->GetHero()->preDamageTrigger = nullptr;
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
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger = nullptr;
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger = nullptr;
            break;
        case TriggerType::USE_HERO_POWER:
            game->triggerManager.useHeroPowerTrigger = nullptr;
            break;
        default:
            break;
    }

    if (m_sequenceType != SequenceType::NONE)
    {
        EraseIf(game->triggers, [this](std::shared_ptr<Trigger> trigger) {
            return trigger.get() == this;
        });
    }
}

void Trigger::ValidateTriggers(Game* game, Entity* source, SequenceType type)
{
    for (auto& trigger : game->triggers)
    {
        if (trigger->m_sequenceType == type)
        {
            trigger->Validate(source);
        }
    }
}

void Trigger::Process(Entity* source)
{
    if (m_sequenceType == SequenceType::NONE)
    {
        Validate(source);
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
        std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(m_owner->player);
        clonedTask->SetSource(m_owner);

        if (const auto playable = dynamic_cast<Playable*>(source); playable)
        {
            clonedTask->SetTarget(playable);
        }
        else
        {
            const auto enchantment = dynamic_cast<Enchantment*>(m_owner);

            if (enchantment != nullptr)
            {
                const auto enchantPlayable =
                    dynamic_cast<Playable*>(enchantment->GetTarget());

                if (enchantPlayable != nullptr)
                {
                    clonedTask->SetTarget(enchantPlayable);
                }
                else
                {
                    clonedTask->SetTarget(nullptr);
                }
            }
            else
            {
                clonedTask->SetTarget(nullptr);
            }
        }

        if (fastExecution)
        {
            clonedTask->Run();
        }
        else
        {
            m_owner->game->taskQueue.Enqueue(std::move(clonedTask));
        }
    }

    m_isValidated = false;
}

void Trigger::Validate(Entity* source)
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
        case TriggerSource::ENEMY:
            if (source && source->player == m_owner->player)
            {
                return;
            }
            break;
        case TriggerSource::HERO:
            if (dynamic_cast<Hero*>(source) == nullptr ||
                (source && source->player != m_owner->player))
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
        case TriggerSource::MINIONS:
            if (dynamic_cast<Minion*>(source) == nullptr ||
                (source && source->player != m_owner->player))
            {
                return;
            }
            break;
        case TriggerSource::MINIONS_EXCEPT_SELF:
            if (dynamic_cast<Minion*>(source) == nullptr ||
                (source && source->player != m_owner->player) ||
                source == m_owner)
            {
                return;
            }
            break;
        case TriggerSource::ENEMY_MINIONS:
            if (dynamic_cast<Minion*>(source) == nullptr ||
                (source && source->player == m_owner->player))
            {
                return;
            }
            break;
        case TriggerSource::ENCHANTMENT_TARGET:
        {
            const auto enchantment = dynamic_cast<Enchantment*>(m_owner);
            if (enchantment == nullptr || source == nullptr ||
                enchantment->GetTarget()->id != source->id)
            {
                return;
            }
            break;
        }
        case TriggerSource::ENEMY_SPELLS:
        {
            if (dynamic_cast<Spell*>(source) == nullptr ||
                (source && source->player == m_owner->player))
            {
                return;
            }
            break;
        }
        case TriggerSource::FRIENDLY:
        {
            if (source == nullptr ||
                (source && source->player != m_owner->player))
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
            if (!eitherTurn &&
                (m_owner == nullptr || source != m_owner->player))
            {
                return;
            }
            break;
        case TriggerType::PLAY_CARD:
        case TriggerType::SUMMON:
        case TriggerType::AFTER_SUMMON:
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
        const auto playable = dynamic_cast<Playable*>(source);
        const bool res = (playable != nullptr) ? condition->Evaluate(playable)
                                               : condition->Evaluate(m_owner);

        if (!res)
        {
            return;
        }
    }

    m_isValidated = true;
}
}  // namespace RosettaStone
