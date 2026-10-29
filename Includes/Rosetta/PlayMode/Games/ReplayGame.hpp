// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_REPLAY_GAME_HPP
#define ROSETTASTONE_PLAYMODE_REPLAY_GAME_HPP

#include <Rosetta/PlayMode/Games/Game.hpp>

#include <effolkronium/random.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief A game that branches by replaying recorded player tasks.
//!
//! All mutations must go through Process(); pointers reachable through
//! GetGame() and GetCurrentPlayer() are for inspection and task construction
//! only. Uses the existing global RNG temporarily, so execution must be
//! single-threaded. Card metadata must remain unchanged throughout the lifetime
//! of the replay.
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

    //! Replays into independent runtime state at a quiescent MAIN_ACTION.
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
