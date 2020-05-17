// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_HPP

#include <Rosetta/Battlegrounds/Enums/GameEnums.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

#include <array>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Game class.
//!
//! This class stores Battlegrounds related states which consists of information
//! of 8 players. Battlegrounds is a game mode where eight players face off in
//! 1v1 rounds, with the goal to be the last player standing. Each round
//! consists of two phases.
//!
class Game
{
 public:
    //! Starts the game.
    void Start();

    //! Processes the select hero phase.
    void SelectHero();

    //! Processes the recruit phase.
    void Recruit();

    //! Processes the combat phase.
    void Combat();

    //! Processes the game over phase.
    void GameOver();

    Phase phase = Phase::INVALID;
    Phase nextPhase = Phase::INVALID;

 private:
    std::array<Player, 8> players;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_HPP
