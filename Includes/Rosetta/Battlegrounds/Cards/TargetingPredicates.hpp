// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_TARGETING_PREDICATES_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TARGETING_PREDICATES_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

#include <functional>

namespace RosettaStone::Battlegrounds
{
class Minion;

using TargetingPredicate = std::function<bool(Minion&)>;

//!
//! \brief TargetingPredicates class.
//!
//! This class includes utility methods for targeting predicate.
//!
class TargetingPredicates
{
 public:
    //! Predicate wrapper for checking the target requires that
    //! it has Race::MURLOC.
    //! \return Generated TargetingPredicate for intended purpose.
    static TargetingPredicate ReqMurlocTarget();

    //! Predicate wrapper for checking the target requires that it has \p race.
    //! \param race The value of race.
    //! \return Generated TargetingPredicate for intended purpose.
    static TargetingPredicate ReqTargetWithRace(Race race);
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TARGETING_PREDICATES_HPP
