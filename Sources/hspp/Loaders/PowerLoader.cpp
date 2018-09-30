// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Enchants/Powers.h>
#include <hspp/Loaders/PowerLoader.h>

namespace Hearthstonepp
{
void PowerLoader::Load(std::vector<Card*>& cards) const
{
    Powers* powers = Powers::GetInstance();

    for (auto& card : cards)
    {
        card->power = powers->FindPowerByCardID(card->id);
    }
}
}  // namespace Hearthstonepp