// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP

#include <Rosetta/Battlegrounds/Enums/GameEnums.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

#include <array>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief GameState struct.
//!
//! This struct stores the information of the game state of all players.
//!
struct GameState
{
    Phase phase = Phase::INVALID;
    Phase nextPhase = Phase::INVALID;

    std::array<Player, 8> players;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP
