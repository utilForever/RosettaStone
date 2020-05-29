// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP

#include <Rosetta/Battlegrounds/Models/Hero.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

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

    Hero hero;
    int currentTier = 1;

    std::vector<std::optional<Minion>> minions;
    std::array<std::optional<Minion>, 6> minionsInTavern;
    std::function<void(Player&)> prepareMinionCallback;

    std::array<int, 4> heroChoices{ 0, 0, 0, 0 };
    std::function<void()> selectHeroCallback;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_PLAYER_HPP
