// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GAME_HPP
#define ROSETTASTONE_GAME_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Managers/TriggerManager.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/EventMetaData.hpp>
#include <Rosetta/Tasks/TaskQueue.hpp>
#include <Rosetta/Tasks/TaskStack.hpp>
#include <Rosetta/Views/ReducedBoardView.hpp>

#include <map>

namespace RosettaStone
{
class ActionParams;

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

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopyFrom(const Game& rhs);

    //! Returns the format type of the game.
    //! \return The format type of the game.
    FormatType GetFormatType() const;

    //! Returns the first player.
    //! \return The first player.
    Player* GetPlayer1();

    //! Returns the first player.
    //! \return The first player.
    const Player* GetPlayer1() const;

    //! Returns the second player.
    //! \return The second player.
    Player* GetPlayer2();

    //! Returns the second player.
    //! \return The second player.
    const Player* GetPlayer2() const;

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player* GetCurrentPlayer();

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    const Player* GetCurrentPlayer() const;

    //! Sets the player controlling the current turn.
    //! \param type The player type controlling the current turn.
    void SetCurrentPlayer(PlayerType type);

    //! Returns the opponent player.
    //! \return The opponent player.
    Player* GetOpponentPlayer();

    //! Returns the opponent player.
    //! \return The opponent player.
    const Player* GetOpponentPlayer() const;

    //! Gets the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Sets the turn of the game.
    //! \param turn The turn of the game.
    void SetTurn(int turn);

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

    //! Updates aura.
    void UpdateAura();

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

    //! Performs selected action.
    //! \param params The action params.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> PerformAction(ActionParams& params);

    //! Creates board view.
    //! \return The reduced board view.
    ReducedBoardView CreateView();

    State state = State::INVALID;

    Step step = Step::INVALID;
    Step nextStep = Step::INVALID;

    std::map<int, Playable*> entityList;
    std::vector<int> rushMinions;

    TaskQueue taskQueue;
    TaskStack taskStack;
    TriggerManager triggerManager;
    std::unique_ptr<EventMetaData> currentEventData;

    std::vector<IAura*> auras;
    std::vector<std::shared_ptr<Trigger>> triggers;
    std::vector<std::pair<Entity*, IEffect*>> oneTurnEffects;
    std::vector<std::shared_ptr<Enchantment>> oneTurnEffectEnchantments;
    std::vector<Minion*> summonedMinions;
    std::map<std::size_t, Minion*> deadMinions;

 private:
    //! Checks whether the game is over.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> CheckGameOver();

    GameConfig m_gameConfig;

    std::array<Player, 2> m_players;
    std::size_t m_turn = 0;

    std::size_t m_entityID = 0;
    std::size_t m_oopIndex = 0;

    PlayerType m_currentPlayer = PlayerType::INVALID;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_HPP
