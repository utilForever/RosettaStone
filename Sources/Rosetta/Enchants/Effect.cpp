// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/Effect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Character.hpp>

#include <stdexcept>

namespace RosettaStone
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}

void Effect::Apply(Character* character, bool isOneTurnEffect)
{
    auto& oneTurnEffects = character->GetOwner().GetGame()->oneTurnEffects;

    if (isOneTurnEffect)
    {
        oneTurnEffects.emplace_back(std::make_pair(character, this));
    }

    const int prevValue = character->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            character->SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SUB:
            character->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::MUL:
            character->SetGameTag(m_gameTag, prevValue * m_value);
            break;
        case EffectOperator::SET:
            character->SetGameTag(m_gameTag, m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Apply(AuraEffects& auraEffects) const
{
    const int prevValue = auraEffects.GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects.SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SUB:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SET:
            auraEffects.SetGameTag(m_gameTag, m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Remove(Character* character) const
{
    const int prevValue = character->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            character->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            character->SetGameTag(
                m_gameTag, character->card.gameTags.at(m_gameTag) + m_value);
            break;
        case EffectOperator::SET:
            character->SetGameTag(m_gameTag, 0);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Remove(AuraEffects& auraEffects) const
{
    if (m_gameTag == GameTag::HEALTH && m_effectOperator == EffectOperator::ADD)
    {
        auto owner = dynamic_cast<Character*>(auraEffects.GetOwner());
        int prevDamage = owner->GetDamage();
        owner->SetDamage(prevDamage - m_value);
    }

    const int prevValue = auraEffects.GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            auraEffects.SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SET:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}
}  // namespace RosettaStone
