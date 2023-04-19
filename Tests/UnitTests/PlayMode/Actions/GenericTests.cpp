// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Generic] - ShuffleIntoDeck")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Playable* coinCard =
        Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                            std::nullopt, curPlayer->GetHandZone());

    Generic::ShuffleIntoDeck(curPlayer, curPlayer->GetHero(), coinCard);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 1);
    CHECK_EQ((*curPlayer->GetDeckZone())[0]->card->id, "GAME_005");
}

TEST_CASE("[Generic] - ShuffleIntoDeck_Full")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Playable* coinCard =
        Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                            std::nullopt, curPlayer->GetHandZone());

    for (std::size_t i = 0; i < MAX_DECK_SIZE; ++i)
    {
        Playable* tempCard =
            Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                                std::nullopt, curPlayer->GetHandZone());
        curPlayer->GetDeckZone()->Add(tempCard);
    }

    Generic::ShuffleIntoDeck(curPlayer, curPlayer->GetHero(), coinCard);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), MAX_DECK_SIZE);
}

TEST_CASE("[Generic] - GetZone")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    CHECK_EQ(curPlayer->GetDeckZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::DECK)->GetType());
    CHECK_EQ(curPlayer->GetFieldZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::PLAY)->GetType());
    CHECK_EQ(curPlayer->GetGraveyardZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::GRAVEYARD)->GetType());
    CHECK_EQ(curPlayer->GetHandZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::HAND)->GetType());
    CHECK_EQ(curPlayer->GetSecretZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::SECRET)->GetType());
    CHECK_EQ(curPlayer->GetSetasideZone()->GetType(),
             Generic::GetZone(curPlayer, ZoneType::SETASIDE)->GetType());
    CHECK_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::INVALID));
    CHECK_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::REMOVEDFROMGAME));
}