// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Enchants/Effect.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}

void Effect::ApplyTo(Entity* entity, bool isOneTurnEffect) const
{
    if (isOneTurnEffect)
    {
        entity->game->oneTurnEffects.emplace_back(
            std::make_pair(entity, new Effect(*this)));
    }

    const int prevValue = entity->GetNativeGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            entity->SetNativeGameTag(m_gameTag, prevValue + m_value);

            if (const auto weapon = dynamic_cast<Weapon*>(entity); weapon)
            {
                if (m_gameTag == GameTag::DURABILITY && prevValue + m_value > 0)
                {
                    weapon->isDestroyed = false;
                }
            }

            break;
        case EffectOperator::SUB:
            entity->SetNativeGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::MUL:
            entity->SetNativeGameTag(m_gameTag, prevValue * m_value);
            break;
        case EffectOperator::SET:
            entity->SetNativeGameTag(m_gameTag, m_value);
            break;
    }
}

void Effect::ApplyTo(PlayerAuraEffects& auraEffects) const
{
    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value + m_value);
            break;
        }
        case EffectOperator::SUB:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value - m_value);
            break;
        }
        case EffectOperator::SET:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value + m_value);
            break;
        }
        default:
            throw std::invalid_argument(
                "Effect::ApplyTo() - Invalid effect operator!");
    }
}

void Effect::ApplyAuraTo(Entity* entity) const
{
    AuraEffects* auraEffects = entity->auraEffects;
    if (!auraEffects)
    {
        auraEffects = new AuraEffects(entity->card->GetCardType());
        entity->auraEffects = auraEffects;
    }

    const int prevValue = auraEffects->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects->SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SUB:
            auraEffects->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SET:
            auraEffects->SetGameTag(m_gameTag, m_value);

            if (const auto minion = dynamic_cast<Minion*>(entity); minion)
            {
                if (m_gameTag == GameTag::HEALTH_MINIMUM)
                {
                    minion->SetGameTag(GameTag::HEALTH_MINIMUM, m_value);
                }
            }

            break;
        default:
            throw std::invalid_argument(
                "Effect::ApplyAuraTo() - Invalid effect operator!");
    }
}

void Effect::RemoveFrom(Entity* entity) const
{
    const int prevValue = entity->GetNativeGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            entity->SetNativeGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            entity->SetNativeGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SET:
            entity->SetNativeGameTag(m_gameTag, 0);
            break;
        default:
            throw std::invalid_argument(
                "Effect::RemoveFrom() - Invalid effect operator!");
    }
}

void Effect::RemoveFrom(PlayerAuraEffects& auraEffects) const
{
    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value - m_value);
            break;
        }
        case EffectOperator::SUB:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value + m_value);
            break;
        }
        case EffectOperator::SET:
        {
            const int value = auraEffects.GetValue(m_gameTag);
            auraEffects.SetValue(m_gameTag, value - m_value);
            break;
        }
        default:
            throw std::invalid_argument(
                "Effect::RemoveFrom() - Invalid effect operator!");
    }
}

void Effect::RemoveAuraFrom(Entity* entity) const
{
    const AuraEffects* auraEffects = entity->auraEffects;
    const int prevValue = auraEffects->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            auraEffects->SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SET:
            auraEffects->SetGameTag(m_gameTag, prevValue - m_value);

            if (const auto minion = dynamic_cast<Minion*>(entity); minion)
            {
                if (m_gameTag == GameTag::HEALTH_MINIMUM)
                {
                    minion->SetGameTag(GameTag::HEALTH_MINIMUM, 0);
                }
            }

            break;
        default:
            throw std::invalid_argument(
                "Effect::RemoveAuraFrom() - Invalid effect operator!");
    }
}

IEffect* Effect::ChangeValue(int newValue) const
{
    return new Effect(m_gameTag, m_effectOperator, newValue);
}

EffectOperator Effect::GetEffectOperator() const
{
    return m_effectOperator;
}

GameTag Effect::GetGameTag() const
{
    return m_gameTag;
}

int Effect::GetValue() const
{
    return m_value;
}
}  // namespace RosettaStone::PlayMode
