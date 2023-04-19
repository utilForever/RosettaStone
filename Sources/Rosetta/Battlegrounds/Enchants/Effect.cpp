// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}

int Effect::GetValue(Minion& minion) const
{
    switch (m_gameTag)
    {
        case GameTag::ATK:
            return minion.GetAttack();
        case GameTag::HEALTH:
            return minion.GetHealth();
        default:
            return 0;
    }
}

void Effect::SetValue(Minion& minion, int value) const
{
    switch (m_gameTag)
    {
        case GameTag::ATK:
            minion.SetAttack(value);
            break;
        case GameTag::HEALTH:
            minion.SetHealth(value);
            break;
        default:
            break;
    }
}

void Effect::ApplyTo(Minion& minion) const
{
    const int prevValue = GetValue(minion);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            SetValue(minion, prevValue + m_value);
            break;
        default:
            throw std::invalid_argument(
                "Effect::ApplyTo() - Invalid effect operator!");
    }
}

Effect Effect::ChangeValue(int newValue) const
{
    return Effect{ m_gameTag, m_effectOperator, newValue };
}
}  // namespace RosettaStone::Battlegrounds
