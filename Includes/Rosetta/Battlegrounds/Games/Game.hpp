// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_HPP

#include <Rosetta/Battlegrounds/Games/GameState.hpp>

#include <atomic>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Game class.
//!
//! This class processes the game, Hearthstone: Battlegrounds. Battlegrounds is
//! a game mode where eight players face off in 1v1 rounds, with the goal to be
//! the last player standing. Each round consists of two phases.
//!
class Game
{
 public:
    //! Gets the game state.
    //! \return The game state.
    GameState& GetGameState();

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

 private:
    GameState m_gameState{};

    Race m_excludeRace = Race::INVALID;
    std::atomic<int> m_playerCount = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_HPP
