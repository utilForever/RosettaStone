// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP

#include <Rosetta/Battlegrounds/Models/Hero.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Zones/FieldZone.hpp>
#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>

#include <array>
#include <functional>
#include <optional>
#include <vector>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Player class.
//!
//! This class stores various information that used in Battlegrounds.
//!
class Player
{
 public:
    //! Initializes a Hero instance.
    //! \param idx The index of hero choices.
    void SelectHero(std::size_t idx);

    //! Fill a list of minions in Tavern for purchase.
    void FillTavernMinions();

    //! Purchases a minion from Tavern's field.
    //! \param idx The index of a list of minions in Tavern's field.
    void PurchaseMinion(std::size_t idx);

    //! Sells a minion to Tavern.
    //! \param idx The index of a list of minions in player's field.
    void SellMinion(std::size_t idx);

    Hero hero;

    int remainCoin = 0;
    int totalCoin = 0;
    int currentTier = 0;

    HandZone handZone{};
    FieldZone minions;
    FieldZone tavernMinions;

    std::array<int, 4> heroChoices{ 0, 0, 0, 0 };

    std::function<void()> selectHeroCallback;
    std::function<void(Player&)> fillTavernMinionCallback;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
