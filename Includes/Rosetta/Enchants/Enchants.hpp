// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ENCHANTS_HPP
#define ROSETTASTONE_ENCHANTS_HPP

#include <Rosetta/Enchants/Enchant.hpp>

#include <string>

namespace RosettaStone
{
//!
//! \brief Enchants class.
//!
//! This class includes utility methods for enchant.
//!
class Enchants
{
 public:
    //! Creates enchant from card's text.
    //! \param cardID A card's ID.
    //! \return A newly created enchant from card's text.
    static Enchant GetEnchantFromText(const std::string& cardID);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANTS_HPP