// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Observation.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

namespace
{
GameConfig FixedConfig()
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.doShuffle = false;

    const std::array ids{
        "CS2_231", "EX1_049", "EX1_015", "CS2_023", "CS2_172",
        "CS2_120", "CS1_042", "EX1_008", "CS2_182", "CS2_119",
        "CS2_200", "CS2_186", "CS2_171", "CS2_189", "LOEA10_3"
    };

    for (std::size_t i = 0; i < config.player1Deck.size(); ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID(ids[i % ids.size()]);
    }

    config.player2Deck = config.player1Deck;

    return config;
}

}  // namespace

TEST_CASE("[Determinization] - PublicEncoderNeverReadsHandsOrDecks")
{
    ReplayGame real(FixedConfig(), 9);
    const auto expected = EncodePublicObservation(real.GetGame());

    CHECK(expected.hand == Observation{}.hand);
    CHECK(expected.chooseOne == Observation{}.chooseOne);
    CHECK_EQ(expected.players[0][ObservationSchema::HAND_COUNT], 4);
    CHECK_EQ(expected.players[1][ObservationSchema::HAND_COUNT], 5);

    std::vector<std::pair<Playable*, Card*>> hidden;
    const auto* actor = real.GetCurrentPlayer();

    for (const auto* player :
         { actor, static_cast<const Player*>(actor->opponent) })
    {
        for (auto* card : player->GetHandZone()->GetAll())
        {
            hidden.emplace_back(card, card->card);
            card->card = nullptr;
        }

        for (auto* card : player->GetDeckZone()->GetAll())
        {
            hidden.emplace_back(card, card->card);
            card->card = nullptr;
        }
    }

    CHECK(EncodePublicObservation(real.GetGame()) == expected);

    for (const auto& [entity, card] : hidden)
    {
        entity->card = card;
    }
}
