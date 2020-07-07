// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_EFFECTS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_EFFECTS_HPP

#include <Rosetta/Battlegrounds/Enchants/Effect.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Effects class.
//!
//! This class lists specific effects such as Taunt, Poisonous and Stealth.
//!
class Effects
{
 public:
    //! Creates effect that increases attack by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effect instance.
    static Effect AttackN(int n)
    {
        return Effect{ GameTag::ATK, EffectOperator::ADD, n };
    }

    //! Creates effect that increases health by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effect instance.
    static Effect HealthN(int n)
    {
        return Effect{ GameTag::HEALTH, EffectOperator::ADD, n };
    }
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_EFFECTS_HPP
