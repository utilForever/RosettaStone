// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/Observation.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>
#include <memory>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
namespace Schema = ObservationSchema;
using Random = effolkronium::random_static;

namespace
{
std::unique_ptr<Game> ObservationGame()
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player2Deck.fill(Cards::FindCardByID("CS2_231"));

    auto game = std::make_unique<Game>(config);
    game->Start();
    game->ProcessUntil(Step::MAIN_ACTION);
    game->GetCurrentPlayer()->SetTotalMana(10);
    return game;
}

Playable* Draw(Player* player, const char* id)
{
    return Generic::DrawCard(player, Cards::FindCardByID(id));
}

Playable* AddToZone(Player* player, const char* id, IZone* zone)
{
    auto* entity = Entity::GetFromCard(player, Cards::FindCardByID(id));
    zone->Add(entity);
    return entity;
}
}  // namespace

TEST_CASE("[Observation] - Hidden information cannot change the encoding")
{
    auto first = ObservationGame();
    auto second = ObservationGame();
    auto* player = second->GetCurrentPlayer();
    auto* opponent = player->opponent;

    SUBCASE("Opponent hand identities and private modifications")
    {
        Draw(first->GetCurrentPlayer()->opponent, "CS2_029");
        auto* hidden = Draw(opponent, "CS2_182");
        hidden->SetCost(0);
        hidden->SetGameTag(GameTag::ATK, 12);
    }
    SUBCASE("Opponent secret identities")
    {
        auto* other = first->GetCurrentPlayer()->opponent;
        AddToZone(other, "EX1_287", other->GetSecretZone());
        AddToZone(opponent, "EX1_289", opponent->GetSecretZone());
    }
    SUBCASE("Both deck identities and order")
    {
        for (auto* owner : { player, opponent })
        {
            auto* deck = owner->GetDeckZone();
            auto* removed = deck->Remove(deck->GetTopCard());
            owner->GetSetasideZone()->Add(removed);
            AddToZone(owner, "CS2_029", deck);
            deck->Swap(deck->GetTopCard(), deck->GetBottomCard());
        }
    }
    SUBCASE("Both deck orders with unchanged contents")
    {
        for (auto* game : { first.get(), second.get() })
        {
            for (auto* owner : { game->GetCurrentPlayer(),
                                 game->GetCurrentPlayer()->opponent })
            {
                AddToZone(owner, "CS2_029", owner->GetDeckZone());
            }
        }
        for (auto* owner : { player, opponent })
        {
            auto* deck = owner->GetDeckZone();
            deck->Swap(deck->GetTopCard(), deck->GetBottomCard());
        }
    }
    SUBCASE("Graveyard, setaside, and history are not a visibility source")
    {
        auto* hidden =
            AddToZone(opponent, "CS2_029", opponent->GetGraveyardZone());
        AddToZone(player, "CS2_182", player->GetSetasideZone());
        opponent->playHistory.emplace_back(hidden, nullptr, 1, 0);
    }
    SUBCASE("Runtime identifiers and order of play")
    {
        for (auto* owner : { player, opponent })
        {
            owner->playerID += 100;
            owner->GetHero()->SetGameTag(GameTag::ENTITY_ID, 1000);
            for (auto* card : owner->GetHandZone()->GetAll())
            {
                card->SetGameTag(GameTag::ENTITY_ID, 2000);
                card->orderOfPlay = 99;
            }
        }
    }
    SUBCASE("Private costs retained on public entities")
    {
        for (auto* game : { first.get(), second.get() })
        {
            auto* owner = game->GetCurrentPlayer();
            game->Process(owner, PlayCardTask(Draw(owner, "CS2_182")));
            game->Process(owner, PlayCardTask(Draw(owner, "CS2_106")));
        }
        player->GetHero()->SetCost(9);
        player->GetFieldZone()->GetAll()[0]->SetCost(8);
        player->GetWeapon().SetCost(7);
    }

    const auto expected = EncodeObservation(*first);
    const auto randomBefore = Random::get_engine();
    CHECK(EncodeObservation(*second) == expected);
    CHECK(EncodeObservation(*second) == expected);
    CHECK(Random::get_engine() == randomBefore);
    Random::discard(19);
    const auto advancedRandom = Random::get_engine();
    CHECK(EncodeObservation(*second) == expected);
    CHECK(Random::get_engine() == advancedRandom);
    Random::engine() = randomBefore;
}

TEST_CASE("[Observation] - Public and actor-visible differences are retained")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();
    auto* opponent = player->opponent;
    game->Process(player, PlayCardTask(Draw(player, "CS2_182")));
    AddToZone(player, "EX1_287", player->GetSecretZone());
    const auto before = EncodeObservation(*game);

    SUBCASE("Hero damage")
    {
        opponent->GetHero()->SetDamage(4);
    }
    SUBCASE("Armor")
    {
        opponent->GetHero()->SetArmor(5);
    }
    SUBCASE("Public mana")
    {
        opponent->SetTotalMana(8);
    }
    SUBCASE("Public hand count")
    {
        Draw(opponent, "CS2_029");
    }
    SUBCASE("Public deck count")
    {
        auto* deck = opponent->GetDeckZone();
        opponent->GetSetasideZone()->Add(deck->Remove(deck->GetTopCard()));
    }
    SUBCASE("Public secret count")
    {
        AddToZone(opponent, "EX1_287", opponent->GetSecretZone());
    }
    SUBCASE("Own hand identity")
    {
        player->GetHandZone()->GetAll()[0]->card =
            Cards::FindCardByID("CS2_182");
    }
    SUBCASE("Own effective hand cost")
    {
        player->GetHandZone()->GetAll()[0]->SetCost(3);
    }
    SUBCASE("Own secret identity")
    {
        player->GetSecretZone()->GetAll()[0]->card =
            Cards::FindCardByID("EX1_289");
    }
    SUBCASE("Visible board flag")
    {
        player->GetFieldZone()->GetAll()[0]->SetGameTag(GameTag::DIVINE_SHIELD,
                                                        1);
    }
    SUBCASE("Turn counter")
    {
        game->SetTurn(game->GetTurn() + 1);
    }

    CHECK_FALSE(EncodeObservation(*game) == before);
}
