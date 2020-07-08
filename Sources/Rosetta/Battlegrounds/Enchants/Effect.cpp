// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

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
}  // namespace RosettaStone::Battlegrounds
