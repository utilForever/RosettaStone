// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Powers.hpp>
#include <Rosetta/Loaders/PowerLoader.hpp>

namespace RosettaStone
{
void PowerLoader::Load(std::vector<Card>& cards)
{
    for (auto& card : cards)
    {
        card.power = Powers::GetInstance().FindPowerByCardID(card.id);
    }
}
}  // namespace RosettaStone
