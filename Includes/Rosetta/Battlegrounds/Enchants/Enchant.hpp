// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP
#define ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP

#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>

#include <vector>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Enchant class.
//!
//! This class stores an enchantment, also known as a buff or debuff. It is a
//! special effect gained by a minion, or in rarer occasions by a weapon.
//!
class Enchant
{
 public:
    //! Constructs enchant with given \p effects.
    //! \param effects A list of effect.
    explicit Enchant(std::vector<Effect> effects);

 private:
    std::vector<Effect> m_effects;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_ENCHANT_HPP
