// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Enchant.hpp>

namespace RosettaStone
{
Enchant::Enchant(GameTag gameTag, EffectOperator effectOperator, int value)
{
    Effect effect(gameTag, effectOperator, value);
    effects.emplace_back(effect);
}

Enchant::Enchant(Effect& effect)
{
    effects.emplace_back(effect);
}

Enchant::Enchant(std::vector<Effect>& _effects, bool _isOneTurnEffect)
    : effects(_effects), isOneTurnEffect(_isOneTurnEffect)
{
    // Do nothing
}

void Enchant::ActivateTo(Entity* entity)
{
    for (auto& effect : effects)
    {
        effect.Apply(entity, isOneTurnEffect);
    }
}
}  // namespace RosettaStone
