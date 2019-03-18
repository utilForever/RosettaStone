// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_GAME_HPP
#define HEARTHSTONEPP_GAME_HPP

#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Games/GameConfig.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
//!
//! \brief Game class.
//!
//! This class stores Hearthstone game states which consists of information of
//! both players.
//!
class Game
{
 public:
    //! Deleted default constructor.
    Game() = delete;

    //! Constructs account with given \p gameConfig.
    //! \param gameConfig The game config holds all configuration values.
    Game(GameConfig& gameConfig);

    //! Default destructor.
    ~Game() = default;

    //! Deleted copy constructor.
    Game(const Game&) = delete;

    //! Deleted move constructor.
    Game(Game&&) = delete;

    //! Deleted copy assignment operator.
    Game& operator=(const Game&) = delete;

    //! Deleted move assignment operator.
    Game& operator=(Game&&) = delete;

    //! Returns the first player.
    //! \return The first player.
    Player& GetPlayer1();

    //! Returns the second player.
    //! \return The second player.
    Player& GetPlayer2();

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player& GetCurrentPlayer() const;

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponentPlayer() const;

    //! Gets the next entity identifier.
    //! \return The next entity ID.
    std::size_t GetNextID();

    //! Gets the next order of play index.
    //! \return The next order of play index.
    std::size_t GetNextOOP();

    //! Part of the game state.
    void BeginFirst();

    //! Part of the game state.
    void BeginShuffle();

    //! Part of the game state.
    void BeginDraw();

    //! Part of the game state.
    void BeginMulligan();

    //! Part of the game state.
    void MainBegin();

    //! Part of the game state.
    void MainReady();

    //! Part of the game state.
    void MainStartTriggers();

    //! Part of the game state.
    void MainResource();

    //! Part of the game state.
    void MainDraw();

    //! Part of the game state.
    void MainStart();

    //! Part of the game state.
    void MainEnd();

    //! Part of the game state.
    void MainCleanUp();

    //! Part of the game state.
    void MainNext();

    //! Part of the game state.
    void FinalWrapUp();

    //! Part of the game state.
    void FinalGameOver();

    //! Starts the game.
    void StartGame();

    State state = State::INVALID;

    Step step = Step::INVALID;
    Step nextStep = Step::INVALID;

 private:
    GameConfig m_gameConfig;

    std::array<Player, 2> m_players;
    std::size_t m_turn = 0;

    std::size_t m_entityID = 0;
    std::size_t m_oopIndex = 0;

    Player* m_firstPlayer = nullptr;
    Player* m_currentPlayer = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_HPP