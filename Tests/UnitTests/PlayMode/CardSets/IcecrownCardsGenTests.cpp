// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/CardSetUtils.hpp>

// ---------------------------------------- MINION - HUNTER
// [ICC_419] Bearshark - COST:3 [ATK:4/HP:3]
// - Race: Beast, Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ICC_419 : Bearshark")
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - ICC_038 : Righteous Protector")
{
    // Do nothing
}