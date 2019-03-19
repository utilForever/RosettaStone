// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_AGENT_HPP
#define HEARTHSTONEPP_GAME_AGENT_HPP

#include <hspp/Games/Game.hpp>

namespace Hearthstonepp
{
//!
//! \brief GameAgent class.
//!
//! This class is derived from Game class.
//!
class GameAgent : public Game
{
 public:
    //! Constructs game agent with given \p gameConfig and policies.
    //! \param gameConfig The game config holds all configuration values.
    //! \param p1Policy The game playing policy for player1.
    //! \param p2Policy The game playing policy for player2.
    GameAgent(GameConfig& gameConfig, IPolicy* p1Policy, IPolicy* p2Policy);

    //! Part of the game state.
    void BeginFirst() override;

    //! Part of the game state.
    void BeginShuffle() override;

    //! Part of the game state.
    void BeginDraw() override;

    //! Part of the game state.
    void BeginMulligan() override;

    //! Part of the game state.
    void MainBegin() override;

    //! Part of the game state.
    void MainReady() override;

    //! Part of the game state.
    void MainStartTriggers() override;

    //! Part of the game state.
    void MainResource() override;

    //! Part of the game state.
    void MainDraw() override;

    //! Part of the game state.
    void MainStart() override;

    //! Part of the game state.
    void MainEnd() override;

    //! Part of the game state.
    void MainCleanUp() override;

    //! Part of the game state.
    void MainNext() override;

    //! Part of the game state.
    void FinalWrapUp() override;

    //! Part of the game state.
    void FinalGameOver() override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_AGENT_HPP