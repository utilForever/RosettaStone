// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    switch (type)
    {
        case TriggerType::PLAY_CARD:
        case TriggerType::AFTER_PLAY_CARD:
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
    : triggerActivation(prototype.triggerActivation),
      triggerSource(prototype.triggerSource),
      tasks(prototype.tasks),
      condition(prototype.condition),
      eitherTurn(prototype.eitherTurn),
      fastExecution(prototype.fastExecution),
      removeAfterTriggered(prototype.removeAfterTriggered),
      m_owner(dynamic_cast<Playable*>(&owner)),
      m_triggerType(prototype.m_triggerType),
      m_sequenceType(prototype.m_sequenceType)
{
    auto triggerFunc = [this](Entity* e) {
        if (percentage == 1.0f || Random::get<float>(0.0f, 1.0f) < percentage)
        {
            Process(e);
        }
    };

    handler = TriggerEventHandler(triggerFunc);
}

std::shared_ptr<Trigger> Trigger::Activate(Playable* source,
                                           TriggerActivation activation,
                                           bool cloning)
{
    if (!cloning && activation != triggerActivation)
    {
        if (triggerActivation != TriggerActivation::HAND_OR_PLAY)
        {
            return nullptr;
        }
    }

    auto instance = std::make_shared<Trigger>(*this, *source);
    Game* game = source->game;

    source->activatedTrigger = instance;

    if (m_sequenceType != SequenceType::NONE)
    {
        game->triggers.emplace_back(instance);
    }

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger += instance->handler;
            break;
        case TriggerType::TURN_END:
            game->triggerManager.endTurnTrigger += instance->handler;
            break;
        case TriggerType::ADD_CARD:
            game->triggerManager.addCardTrigger += instance->handler;
            break;
        case TriggerType::DRAW_CARD:
            game->triggerManager.drawCardTrigger += instance->handler;
            break;
        case TriggerType::PLAY_CARD:
            game->triggerManager.playCardTrigger += instance->handler;
            break;
        case TriggerType::AFTER_PLAY_CARD:
            game->triggerManager.afterPlayCardTrigger += instance->handler;
            break;
        case TriggerType::PLAY_MINION:
            game->triggerManager.playMinionTrigger += instance->handler;
            break;
        case TriggerType::AFTER_PLAY_MINION:
            game->triggerManager.afterPlayMinionTrigger += instance->handler;
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger += instance->handler;
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger += instance->handler;
            break;
        case TriggerType::SECRET_REVEALED:
            game->triggerManager.secretRevealedTrigger += instance->handler;
            break;
        case TriggerType::ZONE:
            game->triggerManager.zoneTrigger += instance->handler;
            break;
        case TriggerType::GIVE_HEAL:
            game->triggerManager.giveHealTrigger += instance->handler;
            break;
        case TriggerType::TAKE_HEAL:
            game->triggerManager.takeHealTrigger += instance->handler;
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger += instance->handler;
            break;
        case TriggerType::AFTER_ATTACK:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->player->GetHero()->afterAttackTrigger +=
                        instance->handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(source);
                    minion->afterAttackTrigger += instance->handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->afterAttackTrigger += instance->handler;
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::AFTER_ATTACKED:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->player->GetHero()->afterAttackedTrigger +=
                        instance->handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(source);
                    minion->afterAttackedTrigger += instance->handler;
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger += instance->handler;
            break;
        case TriggerType::AFTER_SUMMON:
            game->triggerManager.afterSummonTrigger += instance->handler;
            break;
        case TriggerType::DEAL_DAMAGE:
            game->triggerManager.dealDamageTrigger += instance->handler;
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger += instance->handler;
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    source->player->GetHero()->preDamageTrigger +=
                        instance->handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(source);
                    minion->preDamageTrigger += instance->handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->preDamageTrigger += instance->handler;
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger += instance->handler;
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger += instance->handler;
            break;
        case TriggerType::USE_HERO_POWER:
            game->triggerManager.useHeroPowerTrigger += instance->handler;
            break;
        case TriggerType::SHUFFLE_INTO_DECK:
            game->triggerManager.shuffleIntoDeckTrigger += instance->handler;
            break;
        default:
            break;
    }

    return instance;
}

void Trigger::Remove() const
{
    Game* game = m_owner->game;

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger -= handler;
            break;
        case TriggerType::TURN_END:
            game->triggerManager.endTurnTrigger -= handler;
            break;
        case TriggerType::ADD_CARD:
            game->triggerManager.addCardTrigger -= handler;
            break;
        case TriggerType::DRAW_CARD:
            game->triggerManager.drawCardTrigger -= handler;
            break;
        case TriggerType::PLAY_CARD:
            game->triggerManager.playCardTrigger -= handler;
            break;
        case TriggerType::AFTER_PLAY_CARD:
            game->triggerManager.afterPlayCardTrigger -= handler;
            break;
        case TriggerType::PLAY_MINION:
            game->triggerManager.playMinionTrigger -= handler;
            break;
        case TriggerType::AFTER_PLAY_MINION:
            game->triggerManager.afterPlayMinionTrigger -= handler;
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger -= handler;
            break;
        case TriggerType::AFTER_CAST:
            game->triggerManager.afterCastTrigger -= handler;
            break;
        case TriggerType::SECRET_REVEALED:
            game->triggerManager.secretRevealedTrigger -= handler;
            break;
        case TriggerType::ZONE:
            game->triggerManager.zoneTrigger -= handler;
            break;
        case TriggerType::GIVE_HEAL:
            game->triggerManager.giveHealTrigger -= handler;
            break;
        case TriggerType::TAKE_HEAL:
            game->triggerManager.takeHealTrigger -= handler;
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger -= handler;
            break;
        case TriggerType::AFTER_ATTACK:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->player->GetHero()->afterAttackTrigger -= handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->afterAttackTrigger -= handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->afterAttackTrigger -= handler;
                    break;
                }
                default:
                    break;
            }
        case TriggerType::AFTER_ATTACKED:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->player->GetHero()->afterAttackedTrigger -= handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->afterAttackedTrigger -= handler;
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger -= handler;
            break;
        case TriggerType::AFTER_SUMMON:
            game->triggerManager.afterSummonTrigger -= handler;
            break;
        case TriggerType::DEAL_DAMAGE:
            game->triggerManager.dealDamageTrigger -= handler;
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger -= handler;
            break;
        case TriggerType::PREDAMAGE:
            switch (triggerSource)
            {
                case TriggerSource::HERO:
                {
                    m_owner->player->GetHero()->preDamageTrigger -= handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->preDamageTrigger -= handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->preDamageTrigger -= handler;
                    break;
                }
                default:
                    break;
            }
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger -= handler;
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger -= handler;
            break;
        case TriggerType::USE_HERO_POWER:
            game->triggerManager.useHeroPowerTrigger -= handler;
            break;
        case TriggerType::SHUFFLE_INTO_DECK:
            game->triggerManager.shuffleIntoDeckTrigger -= handler;
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

    ProcessTasks(source);

    if (const auto spell = dynamic_cast<Spell*>(m_owner);
        spell && spell->IsSecret() && spell->player->ExtraTriggerSecret())
    {
        ProcessTasks(source);
    }

    m_isValidated = false;
}

void Trigger::ProcessTasks(Entity* source)
{
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
                enchantment->GetTarget()->GetGameTag(GameTag::ENTITY_ID) !=
                    source->GetGameTag(GameTag::ENTITY_ID))
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
        case TriggerSource::FRIENDLY_EVENT_SOURCE:
        {
            if (source == nullptr || source->game == nullptr ||
                source->game->currentEventData == nullptr ||
                source->game->currentEventData->eventSource->player !=
                    m_owner->player)
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
        case TriggerType::AFTER_PLAY_CARD:
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
}  // namespace RosettaStone::PlayMode
