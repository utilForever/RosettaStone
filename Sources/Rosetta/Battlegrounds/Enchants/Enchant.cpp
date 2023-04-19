// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>

namespace RosettaStone::Battlegrounds
{
Enchant::Enchant(Effect effect, bool useScriptTag)
    : m_useScriptTag(useScriptTag)
{
    m_effects.emplace_back(effect);
}

Enchant::Enchant(std::vector<Effect> effects, bool useScriptTag)
    : m_effects(std::move(effects)), m_useScriptTag(useScriptTag)
{
    // Do nothing
}

void Enchant::ActivateTo(Minion& minion, int num)
{
    if (!m_useScriptTag)
    {
        for (auto& effect : m_effects)
        {
            effect.ApplyTo(minion);
        }
    }
    else
    {
        m_effects[0].ChangeValue(num).ApplyTo(minion);
    }
}
}  // namespace RosettaStone::Battlegrounds
