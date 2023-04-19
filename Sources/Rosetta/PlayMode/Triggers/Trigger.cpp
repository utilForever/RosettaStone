// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
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
            m_sequenceType = SequenceType::PLAY_MINION;
            break;
        case TriggerType::AFTER_PLAY_MINION:
            m_sequenceType = SequenceType::AFTER_PLAY_MINION;
            break;
        case TriggerType::CAST_SPELL:
            m_sequenceType = SequenceType::PLAY_SPELL;
            break;
        case TriggerType::AFTER_CAST:
            m_sequenceType = SequenceType::AFTER_PLAY_SPELL;
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

Trigger::Trigger(const Trigger& prototype, Entity& owner)
    : triggerActivation(prototype.triggerActivation),
      triggerSource(prototype.triggerSource),
      tasks(prototype.tasks),
      conditions(prototype.conditions),
      conditionLogic(prototype.conditionLogic),
      curTurn(prototype.curTurn),
      lastTurn(prototype.lastTurn),
      eitherTurn(prototype.eitherTurn),
      fastExecution(prototype.fastExecution),
      removeAfterTriggered(prototype.removeAfterTriggered),
      isMultiTrigger(prototype.isMultiTrigger),
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
                                           bool cloning, bool isMulti)
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

    if (isMulti)
    {
        instance->isMultiTrigger = true;
    }
    else if (!isMultiTrigger)
    {
        source->activatedTrigger = instance;
    }

    if (m_sequenceType != SequenceType::NONE)
    {
        game->triggers.emplace_back(instance);
    }

    switch (m_triggerType)
    {
        case TriggerType::GAME_START:
            game->triggerManager.startGameTrigger += instance->handler;
            break;
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
        case TriggerType::AFTER_DRAW_CARD:
            game->triggerManager.afterDrawCardTrigger += instance->handler;
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
        case TriggerType::GAIN_ATTACK:
            if (triggerSource == TriggerSource::HERO)
            {
                source->player->GetHero()->gainAttackTrigger +=
                    instance->handler;
            }
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
                    const auto minion = dynamic_cast<Minion*>(source);
                    minion->afterAttackTrigger += instance->handler;
                    break;
                }
                case TriggerSource::MINIONS:
                {
                    game->triggerManager.afterAttackTrigger +=
                        instance->handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    const auto minion =
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
                    const auto minion = dynamic_cast<Minion*>(source);
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
                    const auto minion = dynamic_cast<Minion*>(source);
                    minion->preDamageTrigger += instance->handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment = dynamic_cast<Enchantment*>(source);
                    const auto minion =
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
        case TriggerType::DISCARD:
            game->triggerManager.discardTrigger += instance->handler;
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger += instance->handler;
            break;
        case TriggerType::INSPIRE:
            game->triggerManager.inspireTrigger += instance->handler;
            break;
        case TriggerType::EQUIP_WEAPON:
            game->triggerManager.equipWeaponTrigger += instance->handler;
            break;
        case TriggerType::SHUFFLE_INTO_DECK:
            game->triggerManager.shuffleIntoDeckTrigger += instance->handler;
            break;
        case TriggerType::MANA_CRYSTAL:
            game->triggerManager.manaCrystalTrigger += instance->handler;
            break;
        default:
            break;
    }

    return instance;
}

void Trigger::Remove()
{
    if (m_isRemoved || !m_owner)
    {
        return;
    }

    Game* game = m_owner->game;

    if (!game)
    {
        return;
    }

    switch (m_triggerType)
    {
        case TriggerType::GAME_START:
            game->triggerManager.startGameTrigger -= handler;
            break;
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
        case TriggerType::AFTER_DRAW_CARD:
            game->triggerManager.afterDrawCardTrigger -= handler;
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
        case TriggerType::GAIN_ATTACK:
            if (triggerSource == TriggerSource::HERO)
            {
                m_owner->player->GetHero()->gainAttackTrigger -= handler;
            }
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
                    const auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->afterAttackTrigger -= handler;
                    break;
                }
                case TriggerSource::MINIONS:
                {
                    game->triggerManager.afterAttackTrigger -= handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    const auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->afterAttackTrigger -= handler;
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
                    m_owner->player->GetHero()->afterAttackedTrigger -= handler;
                    break;
                }
                case TriggerSource::SELF:
                {
                    const auto minion = dynamic_cast<Minion*>(m_owner);
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
                    const auto minion = dynamic_cast<Minion*>(m_owner);
                    minion->preDamageTrigger -= handler;
                    break;
                }
                case TriggerSource::ENCHANTMENT_TARGET:
                {
                    const auto enchantment =
                        dynamic_cast<Enchantment*>(m_owner);
                    const auto minion =
                        dynamic_cast<Minion*>(enchantment->GetTarget());
                    minion->preDamageTrigger -= handler;
                    break;
                }
                default:
                    break;
            }
            break;
        case TriggerType::TARGET:
            game->triggerManager.targetTrigger -= handler;
            break;
        case TriggerType::DISCARD:
            game->triggerManager.discardTrigger -= handler;
            break;
        case TriggerType::DEATH:
            game->triggerManager.deathTrigger -= handler;
            break;
        case TriggerType::INSPIRE:
            game->triggerManager.inspireTrigger -= handler;
            break;
        case TriggerType::EQUIP_WEAPON:
            game->triggerManager.equipWeaponTrigger -= handler;
            break;
        case TriggerType::SHUFFLE_INTO_DECK:
            game->triggerManager.shuffleIntoDeckTrigger -= handler;
            break;
        case TriggerType::MANA_CRYSTAL:
            game->triggerManager.manaCrystalTrigger -= handler;
            break;
        default:
            break;
    }

    // TODO: Is it correct? :thinking:
    // if (!isMultiTrigger)
    //{
    //    m_owner->activatedTrigger = nullptr;
    //}

    if (m_sequenceType != SequenceType::NONE)
    {
        EraseIf(game->triggers,
                [this](const std::shared_ptr<Trigger>& trigger) {
                    return trigger.get() == this;
                });
    }

    m_isRemoved = true;
}

void Trigger::ValidateTriggers(const Game* game, Entity* source,
                               SequenceType type)
{
    for (auto& trigger : game->triggers)
    {
        // If the owner of the trigger is self, ignore it
        if (trigger->m_owner == source &&
            type == SequenceType::AFTER_PLAY_MINION)
        {
            continue;
        }

        // If transformed or summoned minion tries to activate trigger,
        // ignore it
        if (const auto minion = dynamic_cast<Minion*>(trigger->m_owner);
            minion && (minion->IsTransformed() || minion->IsSummoned()))
        {
            continue;
        }

        // If enchantment tries to activate own trigger, ignore it
        if (const auto enchantment =
                dynamic_cast<Enchantment*>(trigger->m_owner);
            enchantment && enchantment->GetOwner() == source)
        {
            continue;
        }

        if (trigger->m_sequenceType == type)
        {
            trigger->Validate(source);
        }
    }
}

void Trigger::Process(Entity* source)
{
    if (m_isRemoved)
    {
        return;
    }

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

    ProcessTasks(source);

    if (const auto spell = dynamic_cast<Spell*>(m_owner);
        spell && spell->IsSecret() && spell->player->ExtraTriggerSecret())
    {
        ProcessTasks(source);
    }

    if (removeAfterTriggered)
    {
        Remove();
    }

    if (lastTurn > 0)
    {
        ++curTurn;

        if (curTurn == lastTurn)
        {
            Remove();
        }
    }

    m_isValidated = false;
}

void Trigger::ProcessTasks(Entity* source) const
{
    for (const auto& task : tasks)
    {
        if (!m_owner)
        {
            continue;
        }

        std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(m_owner->player);
        clonedTask->SetSource(m_owner);

        if (const auto playable = dynamic_cast<Playable*>(source); playable)
        {
            clonedTask->SetTarget(playable);
        }
        else
        {
            if (const auto enchantment = dynamic_cast<Enchantment*>(m_owner))
            {
                if (const auto enchantPlayable =
                        dynamic_cast<Playable*>(enchantment->GetTarget()))
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
            if (m_owner && m_owner->game)
            {
                m_owner->game->taskQueue.Enqueue(std::move(clonedTask));
            }
        }
    }
}

void Trigger::Validate(Entity* source)
{
    if (!m_owner)
    {
        return;
    }

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
            if (!dynamic_cast<Hero*>(source) ||
                (source && source->player != m_owner->player))
            {
                return;
            }
            break;
        case TriggerSource::ALL_MINIONS:
            if (!dynamic_cast<Minion*>(source))
            {
                return;
            }
            break;
        case TriggerSource::MINIONS:
            if (!dynamic_cast<Minion*>(source) ||
                (source && source->player != m_owner->player))
            {
                return;
            }
            break;
        case TriggerSource::MINIONS_EXCEPT_SELF:
            if (!dynamic_cast<Minion*>(source) ||
                (source && source->player != m_owner->player) ||
                source == m_owner)
            {
                return;
            }
            break;
        case TriggerSource::ENEMY_MINIONS:
            if (!dynamic_cast<Minion*>(source) ||
                (source && source->player == m_owner->player))
            {
                return;
            }
            break;
        case TriggerSource::ENCHANTMENT_TARGET:
        {
            const auto enchantment = dynamic_cast<Enchantment*>(m_owner);
            if (!enchantment || !source ||
                enchantment->GetTarget()->GetGameTag(GameTag::ENTITY_ID) !=
                    source->GetGameTag(GameTag::ENTITY_ID))
            {
                return;
            }
            break;
        }
        case TriggerSource::SPELLS:
        {
            if (!dynamic_cast<Spell*>(source) ||
                (source && source->player != m_owner->player))
            {
                return;
            }
            break;
        }
        case TriggerSource::SPELLS_CASTED_ON_THIS:
        {
            if (!dynamic_cast<Spell*>(source) ||
                (source && source->player != m_owner->player) ||
                !source->game->currentEventData ||
                source->game->currentEventData->eventTarget != m_owner)
            {
                return;
            }
            break;
        }
        case TriggerSource::SPELLS_CASTED_ON_ANOTHER_FRIENDLY:
        {
            if (!dynamic_cast<Spell*>(source) ||
                (source && source->player != m_owner->player) ||
                !source->game->currentEventData ||
                source->game->currentEventData->eventTarget == m_owner)
            {
                return;
            }
            break;
        }
        case TriggerSource::ENEMY_SPELLS:
        {
            if (!dynamic_cast<Spell*>(source) ||
                (source && source->player == m_owner->player))
            {
                return;
            }
            break;
        }
        case TriggerSource::FRIENDLY:
        {
            if (!source || source->player != m_owner->player)
            {
                return;
            }
            break;
        }
        case TriggerSource::FRIENDLY_EVENT_SOURCE:
        {
            if (!source || !source->game || !source->game->currentEventData ||
                source->game->currentEventData->eventSource->player !=
                    m_owner->player)
            {
                return;
            }
            break;
        }
    }

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
        case TriggerType::TURN_END:
            if (!eitherTurn && (!m_owner || source != m_owner->player))
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

    for (const auto& condition : conditions)
    {
        const auto playable = dynamic_cast<Playable*>(source);
        const bool res = playable ? condition->Evaluate(playable)
                                  : condition->Evaluate(m_owner);

        if (conditionLogic == MultiCondLogic::AND && !res)
        {
            return;
        }

        if (conditionLogic == MultiCondLogic::OR && res)
        {
            m_isValidated = true;
            break;
        }
    }

    if (conditionLogic == MultiCondLogic::AND)
    {
        m_isValidated = true;
    }
}
}  // namespace RosettaStone::PlayMode
