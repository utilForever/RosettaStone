// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Enchants/Enchant.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>

#include <utility>

namespace RosettaStone
{
Enchant::Enchant(GameTag gameTag, EffectOperator effectOperator, int value)
{
    auto effect = std::make_unique<Effect>(gameTag, effectOperator, value);
    effects.emplace_back(std::move(effect));
}

Enchant::Enchant(std::unique_ptr<IEffect> effect, bool _useScriptTag,
                 bool _isOneTurnEffect)
    : useScriptTag(_useScriptTag), isOneTurnEffect(_isOneTurnEffect)
{
    effects.emplace_back(std::move(effect));
}

Enchant::Enchant(std::vector<std::unique_ptr<IEffect>> _effects,
                 bool _useScriptTag, bool _isOneTurnEffect)
    : effects(std::move(_effects)),
      useScriptTag(_useScriptTag),
      isOneTurnEffect(_isOneTurnEffect)
{
    // Do nothing
}

void Enchant::ActivateTo(Entity* entity, int num1, int num2)
{
    if (!useScriptTag)
    {
        for (auto& effect : effects)
        {
            effect->ApplyTo(entity, isOneTurnEffect);
        }
    }
    else
    {
        effects[0]->ChangeValue(num1)->ApplyTo(entity, isOneTurnEffect);

        if (effects.size() != 2)
        {
            return;
        }

        if (num2 > 0)
        {
            effects[1]->ChangeValue(num2)->ApplyTo(entity, isOneTurnEffect);
        }
        else
        {
            effects[1]->ChangeValue(num1)->ApplyTo(entity, isOneTurnEffect);
        }
    }
}

void Enchant::RemoveEffect(Entity* target)
{
    for (auto& effect : effects)
    {
        effect->RemoveFrom(target);
    }
}

void Enchant::RemoveEffect(Entity* target, int num1, int num2)
{
    effects[0]->ChangeValue(num1)->RemoveFrom(target);

    if (effects.size() == 1)
    {
        return;
    }

    if (num2 > 0)
    {
        effects[1]->ChangeValue(num2)->RemoveFrom(target);
    }
    else
    {
        effects[1]->ChangeValue(num1)->RemoveFrom(target);
    }

    for (std::size_t i = 2; i < effects.size(); ++i)
    {
        effects[i]->RemoveFrom(target);
    }
}
}  // namespace RosettaStone
