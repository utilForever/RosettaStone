// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Enchant.hpp>

namespace Hearthstonepp
{
Enchant::Enchant(Effect& effect)
{
    m_effects.emplace_back(effect);
}

Enchant::Enchant(std::vector<Effect>& effects)
{
    m_effects = effects;
}

void Enchant::ActivateTo(Character* character)
{
    for (auto& effect : m_effects)
    {
        effect.Apply(character);
    }
}
}  // namespace Hearthstonepp