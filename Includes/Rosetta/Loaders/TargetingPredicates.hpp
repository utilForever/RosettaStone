// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TARGETING_PREDICATES_HPP
#define ROSETTASTONE_TARGETING_PREDICATES_HPP

#include <functional>

namespace RosettaStone
{
class Card;
class Player;
class Character;

using TargetingPredicate = std::function<bool(Character*)>;
using AvailabilityPredicate = std::function<bool(Player*, Card*)>;

//!
//! \brief TargetingPredicates class.
//!
//! This class includes utility methods for targeting predicate.
//!
class TargetingPredicates
{
 public:
    //! Predicate wrapper for checking the target requires combo active.
    //! \return Generated AvailabilityPredicate for intended purpose.
    static AvailabilityPredicate ReqTargetForCombo();
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TARGETING_PREDICATES_HPP
