// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/TargetingPredicates.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
TargetingPredicate TargetingPredicates::ReqMurlocTarget()
{
    return [](Minion& minion) { return minion.GetRace() == Race::MURLOC; };
}

TargetingPredicate TargetingPredicates::ReqTargetWithRace(Race race)
{
    switch (race)
    {
        case Race::MURLOC:
            return ReqMurlocTarget();
        default:
            throw std::invalid_argument(
                "TargetingPredicates::ReqTargetWithRace() - "
                "Race is not implemented!");
    }
}
}  // namespace RosettaStone::Battlegrounds
