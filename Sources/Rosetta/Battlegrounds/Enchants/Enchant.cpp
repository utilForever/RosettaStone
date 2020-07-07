// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>

namespace RosettaStone::Battlegrounds
{
Enchant::Enchant(std::vector<Effect> effects) : m_effects(std::move(effects))
{
    // Do nothing
}
}  // namespace RosettaStone::Battlegrounds
