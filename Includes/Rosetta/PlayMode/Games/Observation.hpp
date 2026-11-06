// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_OBSERVATION_HPP
#define ROSETTASTONE_PLAYMODE_OBSERVATION_HPP

#include <Rosetta/Common/Enums/GameEnums.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace RosettaStone::PlayMode
{
//! Versioned tensor contract; see Documents/ObservationSchema.md.
namespace ObservationSchema
{
inline constexpr std::int32_t VERSION = 1;

// Layout limits are versioned independently of the engine's zone limits.
inline constexpr std::size_t NUM_PLAYERS = 2;
inline constexpr std::size_t BOARD_SLOTS = 7;
inline constexpr std::size_t HAND_SLOTS = 10;
inline constexpr std::size_t SECRET_SLOTS = 5;
inline constexpr std::size_t CHOICE_SLOTS = 4;

enum PlayerIndex : std::size_t
{
    SELF = 0,
    OPPONENT = 1
};

enum CardField : std::size_t
{
    PRESENT = 0,
    CARD_ID = 1,
    COST = 2,
    ATTACK = 3,
    HEALTH = 4,
    MAX_HEALTH = 5,
    ARMOR = 6,
    DURABILITY = 7,
    SPELL_POWER = 8,
    ATTACKS_THIS_TURN = 9,
    FLAGS = 10,
    NUM_CARD_FIELDS = 11
};

enum CardFlag : std::int32_t
{
    EXHAUSTED = 1 << 0,
    FROZEN = 1 << 1,
    IMMUNE = 1 << 2,
    TAUNT = 1 << 3,
    DIVINE_SHIELD = 1 << 4,
    STEALTH = 1 << 5,
    WINDFURY = 1 << 6,
    CHARGE = 1 << 7,
    RUSH = 1 << 8,
    POISONOUS = 1 << 9,
    LIFESTEAL = 1 << 10,
    SILENCED = 1 << 11,
    CANT_ATTACK = 1 << 12,
    CANT_ATTACK_HEROES = 1 << 13,
    RUSH_ATTACKABLE = 1 << 14,
    MEGA_WINDFURY = 1 << 15
};

enum PlayerField : std::size_t
{
    MANA_TOTAL = 0,
    MANA_USED = 1,
    MANA_TEMPORARY = 2,
    OVERLOAD_LOCKED = 3,
    OVERLOAD_OWED = 4,
    HAND_COUNT = 5,
    DECK_COUNT = 6,
    SECRET_COUNT = 7,
    FATIGUE = 8,
    CARDS_PLAYED_THIS_TURN = 9,
    CHOOSE_BOTH = 10,
    NUM_PLAYER_FIELDS = 11
};

enum TurnField : std::size_t
{
    TURN_NUMBER = 0,
    DECISION = 1,
    NUM_TURN_FIELDS = 2
};

enum Decision : std::int32_t
{
    NONE = 0,
    MAIN_ACTION = 1,
    GENERAL_CHOICE = 2
};

using Card = std::array<std::int32_t, NUM_CARD_FIELDS>;
using Player = std::array<std::int32_t, NUM_PLAYER_FIELDS>;

//! Maps an absolute seat to the observation's owner axis.
//! Both arguments must be concrete seats; RANDOM and INVALID are rejected.
constexpr std::size_t RelativePlayerIndex(PlayerType player,
                                          PlayerType actingPlayer)
{
    if ((player != PlayerType::PLAYER1 && player != PlayerType::PLAYER2) ||
        (actingPlayer != PlayerType::PLAYER1 &&
         actingPlayer != PlayerType::PLAYER2))
    {
        throw std::invalid_argument(
            "Observation requires concrete player seats");
    }

    return player == actingPlayer ? SELF : OPPONENT;
}
}  // namespace ObservationSchema

//! Fixed-shape, player-relative observation storage, not a Game encoder.
//! All payload values are int32, unscaled, and zero by default. Owner axes
//! are [acting player, opponent]; slots retain engine zone/offered order.
//! No runtime entity IDs, opponent hand identities, or deck contents belong
//! here. Flattening order is member declaration order, then row-major order;
//! C++ object bytes (including padding) are not a serialization format.
//! shortcut: No graveyard/history features; revise the version when needed.
struct Observation
{
    std::int32_t schemaVersion = ObservationSchema::VERSION;
    std::array<std::int32_t, ObservationSchema::NUM_TURN_FIELDS> turn{};
    std::array<ObservationSchema::Player, ObservationSchema::NUM_PLAYERS>
        players{};
    std::array<ObservationSchema::Card, ObservationSchema::NUM_PLAYERS>
        heroes{};
    std::array<ObservationSchema::Card, ObservationSchema::NUM_PLAYERS>
        heroPowers{};
    std::array<ObservationSchema::Card, ObservationSchema::NUM_PLAYERS>
        weapons{};
    std::array<
        std::array<ObservationSchema::Card, ObservationSchema::BOARD_SLOTS>,
        ObservationSchema::NUM_PLAYERS>
        board{};
    std::array<ObservationSchema::Card, ObservationSchema::HAND_SLOTS> hand{};
    std::array<std::int32_t, ObservationSchema::SECRET_SLOTS> secrets{};
    std::array<std::array<std::int32_t, ObservationSchema::CHOICE_SLOTS>,
               ObservationSchema::HAND_SLOTS>
        chooseOne{};
    std::array<ObservationSchema::Card, ObservationSchema::CHOICE_SLOTS>
        choices{};

    bool operator==(const Observation&) const = default;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_OBSERVATION_HPP
