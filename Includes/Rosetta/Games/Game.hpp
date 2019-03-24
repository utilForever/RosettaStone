// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GAME_HPP
#define ROSETTASTONE_GAME_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
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
    explicit Game(GameConfig& gameConfig);

    //! Default destructor.
    virtual ~Game() = default;

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
    virtual void BeginFirst();

    //! Part of the game state.
    virtual void BeginShuffle();

    //! Part of the game state.
    virtual void BeginDraw();

    //! Part of the game state.
    virtual void BeginMulligan();

    //! Part of the game state.
    virtual void MainBegin();

    //! Part of the game state.
    virtual void MainReady();

    //! Part of the game state.
    virtual void MainStartTriggers();

    //! Part of the game state.
    virtual void MainResource();

    //! Part of the game state.
    virtual void MainDraw();

    //! Part of the game state.
    virtual void MainStart();

    //! Part of the game state.
    virtual void MainEnd();

    //! Part of the game state.
    virtual void MainCleanUp();

    //! Part of the game state.
    virtual void MainNext();

    //! Part of the game state.
    virtual void FinalWrapUp();

    //! Part of the game state.
    virtual void FinalGameOver();

    //! Starts the game.
    void StartGame();

    State state = State::INVALID;

    Step step = Step::INVALID;
    Step nextStep = Step::INVALID;

    std::vector<Entity*> taskStack;

 private:
    GameConfig m_gameConfig;

    std::array<Player, 2> m_players;
    std::size_t m_turn = 0;

    std::size_t m_entityID = 0;
    std::size_t m_oopIndex = 0;

    Player* m_firstPlayer = nullptr;
    Player* m_currentPlayer = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_HPP
