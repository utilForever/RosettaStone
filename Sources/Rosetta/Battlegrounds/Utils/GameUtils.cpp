// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Utils/GameUtils.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
std::size_t GetNumMinionsCanPurchase(int tier)
{
    if (tier == 1)
    {
        return 3;
    }
    else if (tier == 2 || tier == 3)
    {
        return 4;
    }
    else if (tier == 4 || tier == 5)
    {
        return 5;
    }
    else if (tier == 6)
    {
        return 6;
    }

    throw std::invalid_argument("GetNumMinionsCanPurchase() - Incorrect tier");
}
}  // namespace RosettaStone::Battlegrounds
