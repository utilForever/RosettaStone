// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/CardDef.hpp>

#include <utility>

namespace RosettaStone::Battlegrounds
{
CardDef::CardDef(Power _power) : power(std::move(_power))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs)
    : power(std::move(_power)), playReqs(std::move(_playReqs))
{
    // Do nothing
}
}  // namespace RosettaStone::Battlegrounds
