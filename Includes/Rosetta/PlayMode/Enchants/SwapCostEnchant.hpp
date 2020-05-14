// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SWAP_COST_ENCHANT_HPP
#define ROSETTASTONE_PLAYMODE_SWAP_COST_ENCHANT_HPP

#include <Rosetta/PlayMode/Enchants/Enchant.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief SwapCostEnchant class.
//!
//! This class is implementation of a kind of enchantment that it swaps the cost
//! of two cards. (e.g. Prismatic Lens and Tentacled Menace)
//!
class SwapCostEnchant : public Enchant
{
 public:
    //! Activates enchant to \p entity.
    //! \param entity An entity to which enchant is activated.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    void ActivateTo(Entity* entity, int num1 = 0, int num2 = -1) override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SWAP_COST_ENCHANT_HPP
