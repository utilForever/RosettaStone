// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/HeroPower.h>

namespace Hearthstonepp
{
HeroPower::HeroPower(const Card* pCard) : Entity(pCard)
{
    // Do nothing
}

HeroPower::HeroPower(const HeroPower& power) : Entity(power)
{
    // Do nothing
}

HeroPower& HeroPower::operator=(const HeroPower& power)
{
    if (this == &power)
    {
        return *this;
    }

    return *this;
}

HeroPower* HeroPower::Clone() const
{
    return new HeroPower(*this);
}
}  // namespace Hearthstonepp