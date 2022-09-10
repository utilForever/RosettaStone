// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAYER_AURA_EFFECTS_HPP
#define ROSETTASTONE_PLAYMODE_PLAYER_AURA_EFFECTS_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

namespace RosettaStone::PlayMode
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

    //! Returns the value of specific game tag.
    //! \param tag The game tag to get value.
    //! \return The value of specific game tag.
    int GetValue(GameTag tag) const;

    //! Sets the value of specific game tag.
    //! \param tag The game tag to set value.
    //! \param value The value to set.
    void SetValue(GameTag tag, int value);

 private:
    int m_timeOut = 0;
    int m_spellPower = 0;
    int m_spellPowerDouble = 0;
    int m_healingDoesDamage = 0;
    int m_canTargetMinionByHeroPower = 0;
    int m_cantBeFrozen = 0;
    int m_resourcesUsed = 0;
    int m_extraBattlecry = 0;
    int m_extraMinionDeathrattle = 0;
    int m_extraTriggerSecret = 0;
    int m_extraCastSpell = 0;
    int m_megaWindfury = 0;
    int m_chooseBoth = 0;
    int m_heroPowerDamage = 0;
    int m_takeDamageDouble = 0;
    int m_takeOneDamageAtTime = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PLAYER_AURA_EFFECTS_HPP
