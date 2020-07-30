// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_ENCHANTS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_ENCHANTS_HPP

#include <Rosetta/Battlegrounds/Enchants/Effects.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Enchants class.
//!
//! This class includes utility methods for enchant.
//!
class Enchants
{
 public:
    //! Enchant that adds attack and uses script tag.
    inline static Enchant AddAttackScriptTag =
        Enchant{ Effects::AttackN(0), true };

    //! Creates enchant from card's text.
    //! \param cardID A card's ID.
    //! \return A newly created enchant from card's text.
    static Enchant GetEnchantFromText(const std::string& cardID);
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_ENCHANTS_HPP