// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/HeroPower.h>

namespace Hearthstonepp
{
HeroPower::HeroPower(Card& card) : Entity(card)
{
    // Do nothing
}

HeroPower* HeroPower::Clone() const
{
    return new HeroPower(*this);
}
}  // namespace Hearthstonepp