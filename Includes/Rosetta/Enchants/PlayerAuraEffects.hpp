// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYER_AURA_EFFECTS_HPP
#define ROSETTASTONE_PLAYER_AURA_EFFECTS_HPP

#include <Rosetta/Enums/CardEnums.hpp>

namespace RosettaStone
{
//!
//! \brief PlayerAuraEffects class.
//!
//! This class is a collection of controller Tag increments from Auras.
//! Note that these tags tends to be checked when a player plays any cards.
//!
class PlayerAuraEffects
{
 public:
    //! Default constructor.
    PlayerAuraEffects() = default;

    //! Default destructor.
    ~PlayerAuraEffects() = default;

    //! Deleted copy constructor.
    PlayerAuraEffects(const PlayerAuraEffects&) = delete;

    //! Deleted move constructor.
    PlayerAuraEffects(PlayerAuraEffects&&) noexcept = delete;

    //! Deleted copy assignment operator.
    PlayerAuraEffects& operator=(const PlayerAuraEffects&) = delete;

    //! Deleted move assignment operator.
    PlayerAuraEffects& operator=(PlayerAuraEffects&&) noexcept = delete;

    //! Operator overloading for operator[].
    //! \param tag The game tag.
    //! \return The value of game tag.
    int& operator[](GameTag tag);

 private:
    int m_timeOut = 0;
    int m_spellPowerDouble = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_EFFECTS_HPP
