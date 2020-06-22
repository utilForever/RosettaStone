// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP

#include <Rosetta/Battlegrounds/Models/MinionPool.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Common/Enums/GameEnums.hpp>

#include <array>
#include <limits>

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

    MinionPool minionPool;

    std::array<Player, NUM_BATTLEGROUNDS_PLAYERS> players;
    std::size_t numRemainPlayer = NUM_BATTLEGROUNDS_PLAYERS;
    std::size_t ghostPlayerIdx = std::numeric_limits<std::size_t>::max();
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_STATE_HPP
