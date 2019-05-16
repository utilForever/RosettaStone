// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/Trigger.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/ITask.hpp>

#include <stdexcept>

namespace RosettaStone
{
Trigger::Trigger(TriggerType type) : m_triggerType(type)
{
    switch (type)
    {
        case TriggerType::PLAY_CARD:
            m_sequenceType = SequenceType::PLAY_CARD;
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
      m_triggerType(prototype.m_triggerType),
      m_sequenceType(prototype.m_sequenceType),
      m_owner(&owner)
{
    // Do nothing
}

void Trigger::Activate(Entity& source)
{
    auto* instance = new Trigger(*this, source);
    Game* game = source.owner->GetGame();

    source.activatedTrigger = instance;

    switch (m_triggerType)
    {
        case TriggerType::TURN_START:
            game->triggerManager.startTurnTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::TURN_END:
            game->triggerManager.endTurnTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::PLAY_CARD:
            game->triggerManager.playCardTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::CAST_SPELL:
            game->triggerManager.castSpellTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::HEAL:
            game->triggerManager.healTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger =
                std::bind(&Trigger::Process, instance, std::placeholders::_1,
                          std::placeholders::_2);
            break;
        default:
            throw std::invalid_argument(
                "Trigger::Activate() - Invalid trigger type!");
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
        case TriggerType::HEAL:
            game->triggerManager.healTrigger = nullptr;
            break;
        case TriggerType::ATTACK:
            game->triggerManager.attackTrigger = nullptr;
            break;
        case TriggerType::SUMMON:
            game->triggerManager.summonTrigger = nullptr;
            break;
        case TriggerType::TAKE_DAMAGE:
            game->triggerManager.takeDamageTrigger = nullptr;
            break;
        default:
            throw std::invalid_argument(
                "Trigger::Remove() - Invalid trigger type!");
    }

    delete m_owner->activatedTrigger;
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

    ProcessInternal(player, source);
}

void Trigger::ProcessInternal(Player* player, Entity* source)
{
    m_isValidated = false;

    for (auto& task : tasks)
    {
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
            task->Run(*player);
        }
        else
        {
            m_owner->owner->GetGame()->taskQueue.push_back(task);
        }

        if (removeAfterTriggered)
        {
            Remove();
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
        default:
            throw std::invalid_argument(
                "Trigger::Validate() - Invalid source trigger!");
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
        case TriggerType::CAST_SPELL:
        case TriggerType::HEAL:
        case TriggerType::ATTACK:
        case TriggerType::TAKE_DAMAGE:
            break;
        default:
            throw std::invalid_argument(
                "Trigger::Validate() - Invalid trigger type!");
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
