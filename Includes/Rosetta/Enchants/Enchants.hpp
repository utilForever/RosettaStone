// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ENCHANTS_HPP
#define ROSETTASTONE_ENCHANTS_HPP

#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchant.hpp>

#include <memory>
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
    //! Enchant that adds attack and uses script tag.
    inline static Enchant AddAttackScriptTag =
        Enchant(Effects::AttackN(0), true);
    //! Enchant that adds health and uses script tag.
    inline static Enchant AddHealthScriptTag =
        Enchant(Effects::HealthN(0), true);

    //! Enchant that sets attack and uses script tag.
    inline static Enchant SetAttackScriptTag = Enchant(
        std::make_unique<Effect>(GameTag::ATK, EffectOperator::SET, 0), true);
    //! Enchant that sets health and uses script tag.
    inline static Enchant SetHealthScriptTag = Enchant(
        std::make_unique<Effect>(GameTag::HEALTH, EffectOperator::SET, 0),
        true);

    //! Enchant that adds attack/health and uses script tag.
    inline static Enchant AddAttackHealthScriptTag =
        Enchant(Effects::AttackHealthN(0), true);

    //! Enchant that sets attack/health and uses script tag.
    inline static Enchant SetAttackHealthScriptTag =
        Enchant(Effects::SetAttackHealth(0), true);

    //! Creates enchant from card's text.
    //! \param cardID A card's ID.
    //! \return A newly created enchant from card's text.
    static std::unique_ptr<Enchant> GetEnchantFromText(
        const std::string& cardID);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANTS_HPP