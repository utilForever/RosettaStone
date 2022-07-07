// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_GAME_HPP
#define ROSETTASTONE_PLAYMODE_GAME_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/GameEnums.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Managers/TriggerManager.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/EventMetaData.hpp>
#include <Rosetta/PlayMode/Tasks/TaskQueue.hpp>
#include <Rosetta/PlayMode/Tasks/TaskStack.hpp>

#include <map>

namespace RosettaStone::PlayMode
{
class Minion;

//!
//! \brief Game class.
//!
//! This class stores Hearthstone game states which consists of information of
//! both players.
//!
class Game
{
 public:
    //! Constructs game with default values.
    Game();

    //! Constructs game with given \p gameConfig.
    //! \param gameConfig The game config holds all configuration values.
    explicit Game(const GameConfig& gameConfig);

    //! Default destructor.
    ~Game() = default;

    //! Deleted copy constructor.
    Game(const Game&) = delete;

    //! Deleted move constructor.
    Game(Game&&) noexcept = delete;

    //! Deleted copy assignment operator.
    Game& operator=(const Game&) = delete;

    //! Deleted move assignment operator.
    Game& operator=(Game&&) noexcept = delete;

    //! Initializes the game state and player related variables.
    void Initialize();

    //! Gets player's deck.
    //! \param type The player type to get deck.
    std::array<Card*, START_DECK_SIZE> GetPlayerDeck(PlayerType type) const;

    //! Returns the format type of the game.
    //! \return The format type of the game.
    FormatType GetFormatType() const;

    //! Returns the first player.
    //! \return The first player.
    Player* GetPlayer1();

    //! Returns the second player.
    //! \return The second player.
    Player* GetPlayer2();

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player* GetCurrentPlayer();

    //! Sets the player controlling the current turn.
    //! \param type The player type controlling the current turn.
    void SetCurrentPlayer(PlayerType type);

    //! Returns the opponent player.
    //! \return The opponent player.
    Player* GetOpponentPlayer();

    //! Gets the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Sets the turn of the game.
    //! \param turn The turn of the game.
    void SetTurn(int turn);

    //! Gets the next entity identifier.
    //! \return The next entity ID.
    int GetNextID();

    //! Gets the next order of play index.
    //! \return The next order of play index.
    int GetNextOOP();

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
    void MainAction();

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
    void Start();

    // Processes task queue.
    void ProcessTasks();

    //! Processes destroy and updates aura.
    void ProcessDestroyAndUpdateAura();

    //! Processes graveyard.
    void ProcessGraveyard();

    //! Processes minions that have reborn.
    void ProcessReborn();

    //! Updates aura.
    void UpdateAura() const;

    //! Process the specified task.
    //! \param player A player to run task.
    //! \param task The game task to execute.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> Process(Player* player,
                                             std::unique_ptr<ITask> task);

    //! Process the specified task.
    //! \param player A player to run task.
    //! \param task The game task to execute.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> Process(Player* player, ITask&& task);

    //! Process game until given step arriving.
    //! \param step The game step to process until arrival.
    void ProcessUntil(Step step);

    State state = State::INVALID;

    Step step = Step::INVALID;
    Step nextStep = Step::INVALID;

    std::map<int, Playable*> entityList;
    std::vector<Minion*> summonedMinions;
    std::map<std::size_t, Minion*> deadMinions;
    std::map<std::size_t, Minion*> rebornMinions;
    std::vector<int> rushMinions;
    std::vector<int> ghostlyCards;

    TaskQueue taskQueue;
    TaskStack taskStack;
    TriggerManager triggerManager;
    std::unique_ptr<EventMetaData> currentEventData;

    std::vector<IAura*> auras;
    std::vector<std::shared_ptr<Trigger>> triggers;
    std::vector<std::pair<Entity*, IEffect*>> oneTurnEffects;
    std::vector<std::shared_ptr<Enchantment>> oneTurnEffectEnchantments;

 private:
    //! Checks whether the game is over.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> CheckGameOver();

    GameConfig m_gameConfig;

    std::array<Player, 2> m_players;
    int m_turn = 0;
    int m_entityID = 0;
    int m_oopIndex = 0;

    PlayerType m_currentPlayer = PlayerType::INVALID;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_GAME_HPP
