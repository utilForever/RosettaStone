// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Games/Observation.hpp>

#include <type_traits>

using namespace RosettaStone::PlayMode;
namespace Schema = ObservationSchema;

TEST_CASE("[Observation] - Version one shapes and zero defaults")
{
    const Observation observation;

    using Row = std::array<std::int32_t, 11>;
    using Owners = std::array<Row, 2>;
    using Board = std::array<std::array<Row, 7>, 2>;

    static_assert(
        std::is_same_v<decltype(Observation::schemaVersion), std::int32_t>);
    static_assert(std::is_same_v<decltype(Observation::turn),
                                 std::array<std::int32_t, 2>>);
    static_assert(std::is_same_v<decltype(Observation::players), Owners>);
    static_assert(std::is_same_v<decltype(Observation::heroes), Owners>);
    static_assert(std::is_same_v<decltype(Observation::heroPowers), Owners>);
    static_assert(std::is_same_v<decltype(Observation::weapons), Owners>);
    static_assert(std::is_same_v<decltype(Observation::board), Board>);
    static_assert(
        std::is_same_v<decltype(Observation::hand), std::array<Row, 10>>);
    static_assert(std::is_same_v<decltype(Observation::secrets),
                                 std::array<std::int32_t, 5>>);
    static_assert(std::is_same_v<decltype(Observation::chooseOne),
                                 std::array<std::array<std::int32_t, 4>, 10>>);
    static_assert(
        std::is_same_v<decltype(Observation::choices), std::array<Row, 4>>);

    CHECK_EQ(Schema::VERSION, 1);
    CHECK_EQ(observation.schemaVersion, 1);
    CHECK(observation.turn == decltype(Observation::turn){});
    CHECK(observation.players == Owners{});
    CHECK(observation.heroes == Owners{});
    CHECK(observation.heroPowers == Owners{});
    CHECK(observation.weapons == Owners{});
    CHECK(observation.board == Board{});
    CHECK(observation.hand == decltype(Observation::hand){});
    CHECK(observation.secrets == decltype(Observation::secrets){});
    CHECK(observation.chooseOne == decltype(Observation::chooseOne){});
    CHECK(observation.choices == decltype(Observation::choices){});
    CHECK(observation == Observation{});
}

TEST_CASE("[Observation] - Version one field and flag ordering")
{
    using namespace Schema;

    const std::array cardFields{
        PRESENT,     CARD_ID,           COST,  ATTACK,
        HEALTH,      MAX_HEALTH,        ARMOR, DURABILITY,
        SPELL_POWER, ATTACKS_THIS_TURN, FLAGS
    };
    const std::array playerFields{ MANA_TOTAL,     MANA_USED,
                                   MANA_TEMPORARY, OVERLOAD_LOCKED,
                                   OVERLOAD_OWED,  HAND_COUNT,
                                   DECK_COUNT,     SECRET_COUNT,
                                   FATIGUE,        CARDS_PLAYED_THIS_TURN,
                                   CHOOSE_BOTH };
    const std::array flags{ EXHAUSTED,
                            FROZEN,
                            IMMUNE,
                            TAUNT,
                            DIVINE_SHIELD,
                            STEALTH,
                            WINDFURY,
                            CHARGE,
                            RUSH,
                            POISONOUS,
                            LIFESTEAL,
                            SILENCED,
                            CANT_ATTACK,
                            CANT_ATTACK_HEROES,
                            RUSH_ATTACKABLE,
                            MEGA_WINDFURY };

    CHECK_EQ(NUM_CARD_FIELDS, cardFields.size());
    CHECK_EQ(NUM_PLAYER_FIELDS, playerFields.size());

    for (std::size_t index = 0; index < cardFields.size(); ++index)
    {
        CHECK_EQ(cardFields[index], index);
        CHECK_EQ(playerFields[index], index);
    }

    for (std::size_t index = 0; index < flags.size(); ++index)
    {
        CHECK_EQ(flags[index], std::int32_t{ 1 } << index);
    }

    CHECK_EQ(TURN_NUMBER, 0);
    CHECK_EQ(DECISION, 1);
    CHECK_EQ(NUM_TURN_FIELDS, 2);
    CHECK_EQ(NONE, 0);
    CHECK_EQ(MAIN_ACTION, 1);
    CHECK_EQ(GENERAL_CHOICE, 2);
    CHECK_EQ(SELF, 0);
    CHECK_EQ(OPPONENT, 1);
}

TEST_CASE("[Observation] - Relative owners preserve board slot order")
{
    using namespace Schema;

    CHECK_EQ(RelativePlayerIndex(PlayerType::PLAYER1, PlayerType::PLAYER1), 0);
    CHECK_EQ(RelativePlayerIndex(PlayerType::PLAYER2, PlayerType::PLAYER1), 1);
    CHECK_EQ(RelativePlayerIndex(PlayerType::PLAYER1, PlayerType::PLAYER2), 1);
    CHECK_EQ(RelativePlayerIndex(PlayerType::PLAYER2, PlayerType::PLAYER2), 0);

    std::array<std::array<Schema::Card, 7>, 2> absoluteBoard{};
    absoluteBoard[0][0][HEALTH] = 2;
    absoluteBoard[0][1][HEALTH] = 5;
    absoluteBoard[1][0][HEALTH] = 7;
    absoluteBoard[1][1][HEALTH] = 3;

    Observation firstPerspective;
    firstPerspective
        .board[RelativePlayerIndex(PlayerType::PLAYER1, PlayerType::PLAYER1)] =
        absoluteBoard[0];
    firstPerspective
        .board[RelativePlayerIndex(PlayerType::PLAYER2, PlayerType::PLAYER1)] =
        absoluteBoard[1];

    Observation secondPerspective;
    secondPerspective
        .board[RelativePlayerIndex(PlayerType::PLAYER1, PlayerType::PLAYER2)] =
        absoluteBoard[0];
    secondPerspective
        .board[RelativePlayerIndex(PlayerType::PLAYER2, PlayerType::PLAYER2)] =
        absoluteBoard[1];

    CHECK(secondPerspective.board[SELF] == firstPerspective.board[OPPONENT]);
    CHECK(secondPerspective.board[OPPONENT] == firstPerspective.board[SELF]);
    CHECK_EQ(secondPerspective.board[SELF][0][HEALTH], 7);
    CHECK_EQ(secondPerspective.board[SELF][1][HEALTH], 3);
    CHECK_EQ(secondPerspective.board[OPPONENT][0][HEALTH], 2);
    CHECK_EQ(secondPerspective.board[OPPONENT][1][HEALTH], 5);

    // Rename the seats and the acting seat together: the observation is equal.
    Observation renamedSeats;
    renamedSeats
        .board[RelativePlayerIndex(PlayerType::PLAYER2, PlayerType::PLAYER2)] =
        absoluteBoard[0];
    renamedSeats
        .board[RelativePlayerIndex(PlayerType::PLAYER1, PlayerType::PLAYER2)] =
        absoluteBoard[1];
    CHECK(renamedSeats == firstPerspective);
}

TEST_CASE("[Observation] - Relative owners require concrete seats")
{
    for (const auto invalid :
         { PlayerType::INVALID, PlayerType::RANDOM, static_cast<PlayerType>(-1),
           static_cast<PlayerType>(99) })
    {
        CHECK_THROWS_AS(
            Schema::RelativePlayerIndex(invalid, PlayerType::PLAYER1),
            std::invalid_argument);
        CHECK_THROWS_AS(
            Schema::RelativePlayerIndex(PlayerType::PLAYER2, invalid),
            std::invalid_argument);
        CHECK_THROWS_AS(Schema::RelativePlayerIndex(invalid, invalid),
                        std::invalid_argument);
    }
}
