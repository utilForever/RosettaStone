// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_REPLAY_GAME_HPP
#define ROSETTASTONE_PLAYMODE_REPLAY_GAME_HPP

#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

#include <effolkronium/random.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief A game that branches by replaying recorded player tasks.
//!
//! All mutations must go through Process() or ApplyAction(). Pointers from
//! GetGame() and GetCurrentPlayer() are for inspection and task construction
//! only. Each replay owns its random state; startup and recorded tasks install
//! it temporarily in the existing global RNG and restore the caller's state.
//! Execution must be single-threaded. Fixed seeds reproduce outcomes within
//! the same engine build, action schema, and unchanged card metadata, not
//! across different standard-library implementations or data versions.
//!
class ReplayGame
{
 public:
    //! Starts a game with automatic turn progression and a skipped mulligan.
    //! \param gameConfig The initial game configuration.
    //! \param seed The random seed shared by this game and its branches.
    //! \throws std::invalid_argument If mulligan is enabled, hero classes are
    //! invalid, or the starting player is unsupported.
    ReplayGame(const GameConfig& gameConfig, unsigned int seed);

    //! Returns the game for inspection only, including its entity ID lookup.
    //! \return The game owned by this replay.
    const Game& GetGame() const;

    //! Returns the current player for inspection and task construction only.
    //! \return The player whose turn is active.
    const Player* GetCurrentPlayer() const;

    //! Records and executes a built-in player task for the current player.
    //! Custom tasks and pointers belonging to another game are rejected.
    //! Choices must contain exactly one offered entity ID.
    //! \param task The player task to record and execute.
    //! \return The play states of player 1 and player 2, in that order.
    std::tuple<PlayState, PlayState> Process(ITask&& task);

    //! Validates and records a semantic decision using the normal task path.
    //! Invalid decisions leave the game, history, and random state unchanged.
    //! \param action An action from EnumerateActions(GetGame()).
    //! \return The play states of player 1 and player 2, in that order.
    //! \throws std::invalid_argument If the action is not currently legal.
    //! \throws std::logic_error If the replay failed or is not ready.
    std::tuple<PlayState, PlayState> ApplyAction(const PlayerAction& action);

    //! Returns PLAYING, WON, LOST, or TIED from a fixed player's perspective.
    //! \param player PLAYER1 or PLAYER2, independent of whose turn it is.
    //! \return The requested player's outcome, including after game over.
    //! \throws std::invalid_argument If the player is not a concrete seat.
    //! \throws std::logic_error If the replay failed.
    PlayState GetOutcome(PlayerType player) const;

    //! Returns +1 for a win, -1 for a loss, and 0 for a draw or ongoing game.
    //! \param player PLAYER1 or PLAYER2, independent of whose turn it is.
    //! \return The terminal reward; uses the same validation as GetOutcome().
    int GetReward(PlayerType player) const;

    //! Replays into independent runtime state at a quiescent MAIN_ACTION.
    //! Reconstructs the random state from the initial seed and recorded tasks.
    //! Throws for pending choices, unfinished tasks, failed or terminal games.
    //! \return An independent replay with the same history and random state.
    std::unique_ptr<ReplayGame> Branch() const;

 private:
    struct RecordedTask
    {
        int sourceID = -1;
        int targetID = -1;
        std::unique_ptr<ITask> task;
    };

    //! Validates entity ownership before recording a game-local ID.
    //! \param entity The source or target entity to identify.
    //! \return The entity ID, or -1 for nullptr.
    //! \throws std::invalid_argument If the entity is not registered in this
    //! game.
    int GetEntityID(const Entity* entity) const;

    //! Resolves recorded IDs and executes a task using this replay's RNG.
    //! Marks the replay as failed and rethrows if task application throws.
    //! \param record The recorded task with its source and target IDs.
    //! \return The play states of player 1 and player 2, in that order.
    std::tuple<PlayState, PlayState> Apply(const RecordedTask& record);

    //! Checks that the game is running at MAIN_ACTION with no pending effects.
    //! \throws std::logic_error If the replay failed or the game is not ready.
    void CheckReady() const;

    GameConfig m_config;
    unsigned int m_seed;
    effolkronium::random_static::engine_type m_random;
    std::unique_ptr<Game> m_game;
    std::vector<RecordedTask> m_history;
    bool m_failed = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_REPLAY_GAME_HPP
