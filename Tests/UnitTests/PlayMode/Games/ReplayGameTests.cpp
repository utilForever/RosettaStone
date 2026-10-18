// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <sstream>
#include <stdexcept>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using Random = effolkronium::random_static;

namespace
{
GameConfig ReplayConfig()
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player2Deck.fill(Cards::FindCardByID("CS2_120"));

    return config;
}

Playable* InHand(const ReplayGame& replay, const std::string& cardID)
{
    for (auto* card : replay.GetCurrentPlayer()->GetHandZone()->GetAll())
    {
        if (card->card->id == cardID)
        {
            return card;
        }
    }

    throw std::runtime_error("Test card missing from hand: " + cardID);
}

std::string StateOf(const ReplayGame& replay)
{
    const auto& game = replay.GetGame();
    std::ostringstream out;

    out << static_cast<int>(game.state) << ':' << static_cast<int>(game.step)
        << ':' << static_cast<int>(game.nextStep) << ':' << game.GetTurn()
        << ':' << static_cast<int>(replay.GetCurrentPlayer()->playerType);

    const auto tags = [&out](const Entity* entity) {
        for (const auto& [tag, value] : entity->GetGameTags())
        {
            out << ',' << static_cast<int>(tag) << '=' << value;
        }
    };

    for (const auto* player :
         { replay.GetCurrentPlayer(),
           static_cast<const Player*>(replay.GetCurrentPlayer()->opponent) })
    {
        out << "|player:" << static_cast<int>(player->playerType) << ':'
            << static_cast<int>(player->playState);

        tags(player);

        const auto zone = [&out](const auto* zone) {
            out << "|zone:" << static_cast<int>(zone->GetType());
            for (const auto* entity : zone->GetAll())
            {
                out << ',' << entity->GetGameTag(GameTag::ENTITY_ID);
            }
        };

        zone(player->GetDeckZone());
        zone(player->GetFieldZone());
        zone(player->GetHandZone());
        zone(player->GetGraveyardZone());
        zone(player->GetSecretZone());
        zone(player->GetSetasideZone());

        out << "|history:" << player->playHistory.size();

        for (const auto* card : player->cardsPlayedThisTurn)
        {
            out << ',' << card->id;
        }
    }

    for (const auto& [id, entity] : game.entityList)
    {
        out << "|entity:" << id << ':' << entity->card->id << ':'
            << entity->orderOfPlay << ':' << entity->isDestroyed << ':'
            << entity->GetCost();

        tags(entity);

        if (const auto* character = dynamic_cast<const Character*>(entity))
        {
            out << ':' << character->GetAttack() << ':'
                << character->GetHealth();
        }

        for (const auto& enchantment : entity->appliedEnchantments)
        {
            out << "|enchantment:" << enchantment->card->id;
            tags(enchantment.get());
        }
    }

    out << "|effects:" << game.auras.size() << ':' << game.triggers.size()
        << ':' << game.oneTurnEffects.size() << ':'
        << game.oneTurnEffectEnchantments.size();

    return out.str();
}

void CheckIndependent(const ReplayGame& source, const ReplayGame& child)
{
    const auto& game = child.GetGame();
    const auto* player = child.GetCurrentPlayer();

    REQUIRE_NE(player, source.GetCurrentPlayer());
    CHECK_EQ(player->game, &game);
    CHECK_EQ(player->opponent->game, &game);
    CHECK_EQ(player->opponent->opponent, player);
    CHECK_EQ(game.entityList.size(), source.GetGame().entityList.size());

    for (const auto& [id, entity] : game.entityList)
    {
        const auto* original = source.GetGame().entityList.at(id);

        CHECK_NE(entity, original);
        CHECK_EQ(entity->game, &game);
        CHECK_EQ(entity->player->game, &game);
        CHECK_EQ(entity->card, original->card);

        if (entity->zone)
        {
            CHECK_NE(entity->zone, original->zone);
        }

        if (entity->auraEffects)
        {
            CHECK_NE(entity->auraEffects, original->auraEffects);
        }

        if (entity->ongoingEffect)
        {
            CHECK_NE(entity->ongoingEffect, original->ongoingEffect);
        }

        if (entity->activatedTrigger)
        {
            CHECK_NE(entity->activatedTrigger, original->activatedTrigger);
        }

        for (const auto& enchantment : entity->appliedEnchantments)
        {
            CHECK_EQ(enchantment->game, &game);
            CHECK_EQ(enchantment->GetOwner()->game, &game);
            CHECK_EQ(enchantment->GetTarget()->game, &game);
        }
    }

    for (const auto& [entity, effect] : game.oneTurnEffects)
    {
        CHECK_EQ(entity->game, &game);
    }

    if (game.currentEventData)
    {
        if (game.currentEventData->eventSource)
        {
            CHECK_EQ(game.currentEventData->eventSource->game, &game);
        }

        if (game.currentEventData->eventTarget)
        {
            CHECK_EQ(game.currentEventData->eventTarget->game, &game);
        }
    }
}
}  // namespace

TEST_CASE("[ReplayGame] - BranchIndependence")
{
    auto config = ReplayConfig();
    const std::array cards{ "CS2_231", "NEW1_019", "CS2_122", "CS2_038",
                            "CS2_024", "EX1_277",  "CS2_045" };

    for (std::size_t i = 0; i < cards.size(); ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID(cards[i]);
    }

    auto parent = std::make_unique<ReplayGame>(config, 42);

    auto* wisp = InHand(*parent, "CS2_231");
    const int wispID = wisp->GetGameTag(GameTag::ENTITY_ID);
    parent->Process(PlayCardTask(wisp));
    parent->Process(EndTurnTask());
    parent->Process(EndTurnTask());

    auto* juggler = InHand(*parent, "NEW1_019");
    parent->Process(PlayCardTask(juggler));
    parent->Process(EndTurnTask());
    parent->Process(PlayCardTask(InHand(*parent, "CS2_120")));
    parent->Process(EndTurnTask());

    auto* raidLeader = InHand(*parent, "CS2_122");
    const int raidLeaderID = raidLeader->GetGameTag(GameTag::ENTITY_ID);
    parent->Process(PlayCardTask(raidLeader));
    parent->Process(EndTurnTask());
    parent->Process(EndTurnTask());
    parent->Process(EndTurnTask());
    parent->Process(EndTurnTask());

    REQUIRE_EQ(wisp->GetGameTag(GameTag::ATK), 2);

    parent->Process(EndTurnTask());
    parent->Process(EndTurnTask());

    const auto enchantmentTags = Cards::FindCardByID("CS2_038e")->gameTags;

    parent->Process(PlayCardTask(InHand(*parent, "CS2_038"), wisp));

    CHECK(Cards::FindCardByID("CS2_038e")->gameTags == enchantmentTags);

    parent->Process(PlayCardTask(InHand(*parent, "CS2_045"),
                                 parent->GetCurrentPlayer()->GetHero()));

    REQUIRE_EQ(parent->GetGame().GetTurn(), 11);
    REQUIRE_EQ(parent->GetCurrentPlayer()->GetHero()->GetAttack(), 3);
    REQUIRE_FALSE(parent->GetGame().auras.empty());
    REQUIRE(juggler->activatedTrigger);
    REQUIRE_FALSE(parent->GetGame().oneTurnEffects.empty());
    REQUIRE_FALSE(wisp->appliedEnchantments.empty());

    const auto before = StateOf(*parent);
    const auto randomBefore = Random::get_engine();

    auto child = parent->Branch();
    auto sibling = parent->Branch();

    CHECK(Random::get_engine() == randomBefore);
    CHECK_EQ(StateOf(*parent), before);
    CHECK_EQ(StateOf(*child), before);
    CHECK_EQ(StateOf(*sibling), before);
    CheckIndependent(*parent, *child);
    CheckIndependent(*child, *sibling);

    auto* childField = child->GetCurrentPlayer()->GetFieldZone();
    auto* childWisp =
        dynamic_cast<Minion*>(child->GetGame().entityList.at(wispID));

    child->Process(PlayCardTask(InHand(*child, "CS2_024"),
                                child->GetGame().entityList.at(raidLeaderID)));

    REQUIRE_EQ(childField->GetCount(), 2);
    CHECK_EQ(childWisp->GetAttack(), 1);

    child->Process(PlayCardTask(InHand(*child, "CS2_231")));

    CHECK_EQ(childField->GetCount(), 3);

    child->Process(EndTurnTask());

    CHECK_EQ(childWisp->GetAttack(), 1);
    CHECK_EQ(child->GetCurrentPlayer()->opponent->GetHero()->GetAttack(), 0);
    CHECK(child->GetGame().oneTurnEffects.empty());
    CHECK_EQ(StateOf(*parent), before);
    CHECK_EQ(StateOf(*sibling), before);
    CHECK(Random::get_engine() == randomBefore);

    auto grandchild = child->Branch();

    CHECK_EQ(StateOf(*grandchild), StateOf(*child));
    CheckIndependent(*child, *grandchild);

    parent.reset();
    child.reset();

    grandchild->Process(EndTurnTask());
    grandchild->Process(PlayCardTask(InHand(*grandchild, "CS2_231")));

    CHECK_EQ(grandchild->GetCurrentPlayer()->GetFieldZone()->GetCount(), 4);

    auto* enemyHero = grandchild->GetCurrentPlayer()->opponent->GetHero();
    const int health = enemyHero->GetHealth();

    grandchild->Process(
        AttackTask(grandchild->GetGame().entityList.at(wispID), enemyHero));

    CHECK_EQ(enemyHero->GetHealth(), health - 1);

    grandchild->Process(
        HeroPowerTask(grandchild->GetGame().entityList.at(wispID)));

    CHECK_EQ(grandchild->GetGame().entityList.at(wispID)->GetZoneType(),
             ZoneType::GRAVEYARD);
    CHECK_EQ(grandchild->GetCurrentPlayer()->GetFieldZone()->GetCount(), 4);
    CHECK_EQ(StateOf(*sibling), before);
}

TEST_CASE("[ReplayGame] - CombatSummons")
{
    std::string defenderID;
    int expectedMinions = 0;
    int expectedTidecallerAttack = 0;

    SUBCASE("Deathrattle")
    {
        defenderID = "FP1_002";  // Haunted Creeper
        expectedMinions = 3;
        expectedTidecallerAttack = 1;
    }

    SUBCASE("Reborn")
    {
        defenderID = "ULD_723";  // Murmy
        expectedMinions = 2;
        expectedTidecallerAttack = 3;
    }

    auto config = ReplayConfig();
    config.player1Deck.fill(Cards::FindCardByID("CS2_120"));
    config.player2Deck.fill(Cards::FindCardByID(defenderID));
    config.player2Deck[0] = Cards::FindCardByID("EX1_509");

    ReplayGame parent(config, 42);
    parent.Process(EndTurnTask());
    parent.Process(PlayCardTask(InHand(parent, "EX1_509")));
    parent.Process(EndTurnTask());
    parent.Process(PlayCardTask(InHand(parent, "CS2_120")));
    parent.Process(EndTurnTask());
    parent.Process(PlayCardTask(InHand(parent, defenderID)));
    parent.Process(EndTurnTask());

    const auto before = StateOf(parent);

    auto child = parent.Branch();
    auto sibling = parent.Branch();

    const auto* player = child->GetCurrentPlayer();
    auto* enemyField = player->opponent->GetFieldZone();

    child->Process(
        AttackTask(player->GetFieldZone()->GetAll().front(), (*enemyField)[1]));

    CHECK_EQ(enemyField->GetCount(), expectedMinions);
    CHECK_EQ((*enemyField)[0]->GetAttack(), expectedTidecallerAttack);
    CHECK(child->GetGame().summonedMinions.empty());
    CHECK(child->GetGame().deadMinions.empty());
    CHECK(child->GetGame().rebornMinions.empty());
    CHECK(child->GetGame().taskQueue.IsIdle());

    auto grandchild = child->Branch();

    CHECK_EQ(StateOf(*grandchild), StateOf(*child));

    child->Process(EndTurnTask());
    grandchild->Process(EndTurnTask());

    CHECK_EQ(StateOf(*grandchild), StateOf(*child));
    CHECK_EQ(StateOf(parent), before);
    CHECK_EQ(StateOf(*sibling), before);
}

TEST_CASE("[ReplayGame] - TradeSummons")
{
    auto config = ReplayConfig();
    config.player1Class = CardClass::DRUID;
    config.player1Deck.fill(Cards::FindCardByID("CS2_008"));
    config.player1Deck[0] =
        Cards::FindCardByID("SW_055");  // Impatient Shopkeep
    config.player1Deck[4] = Cards::FindCardByID("DRG_320t");  // Dream Portal

    ReplayGame parent(config, 42);

    const auto before = StateOf(parent);
    const auto randomBefore = Random::get_engine();

    auto child = parent.Branch();
    auto sibling = parent.Branch();

    child->Process(TradeCardTask(InHand(*child, "SW_055")));

    CHECK_EQ(child->GetCurrentPlayer()->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(child->GetCurrentPlayer()->GetRemainingMana(), 0);
    CHECK(child->GetGame().summonedMinions.empty());
    CHECK(child->GetGame().taskQueue.IsIdle());

    auto grandchild = child->Branch();

    CHECK_EQ(StateOf(*grandchild), StateOf(*child));

    child->Process(EndTurnTask());
    grandchild->Process(EndTurnTask());

    CHECK_EQ(StateOf(*grandchild), StateOf(*child));
    CHECK_EQ(StateOf(parent), before);
    CHECK_EQ(StateOf(*sibling), before);
    CHECK(Random::get_engine() == randomBefore);
}

TEST_CASE("[ReplayGame] - DeterministicReplay")
{
    auto config = ReplayConfig();
    config.startPlayer = PlayerType::RANDOM;
    config.doShuffle = true;
    config.player1Deck.fill(Cards::FindCardByID("EX1_277"));
    config.player2Deck.fill(Cards::FindCardByID("EX1_277"));
    config.player1Deck[0] = Cards::FindCardByID("CS2_231");
    config.player2Deck[0] = Cards::FindCardByID("CS2_231");

    const auto globalRandom = Random::get_engine();
    ReplayGame parent(config, 123);

    parent.Process(PlayCardTask(InHand(parent, "EX1_277")));

    auto first = parent.Branch();

    Random::discard(23);

    const auto advancedGlobalRandom = Random::get_engine();
    auto second = parent.Branch();

    CHECK(Random::get_engine() == advancedGlobalRandom);
    CHECK_EQ(StateOf(*first), StateOf(parent));
    CHECK_EQ(StateOf(*first), StateOf(*second));

    first->Process(EndTurnTask());
    first->Process(PlayCardTask(InHand(*first, "EX1_277")));
    second->Process(EndTurnTask());
    second->Process(PlayCardTask(InHand(*second, "EX1_277")));

    CHECK_EQ(StateOf(*first), StateOf(*second));
    CHECK(Random::get_engine() == advancedGlobalRandom);

    Random::engine() = globalRandom;
}

TEST_CASE("[ReplayGame] - CardMetadata")
{
    auto config = ReplayConfig();
    config.player1Deck[0] = Cards::FindCardByID("SCH_525");  // In Formation!

    const auto wispTags = Cards::FindCardByID("CS2_231")->gameTags;
    ReplayGame parent(config, 17);

    parent.Process(EndTurnTask());
    parent.Process(EndTurnTask());
    parent.Process(PlayCardTask(InHand(parent, "SCH_525")));

    CHECK(Cards::FindCardByID("CS2_231")->gameTags == wispTags);

    auto child = parent.Branch();

    CHECK_EQ(StateOf(*child), StateOf(parent));
    CHECK(Cards::FindCardByID("CS2_231")->gameTags == wispTags);
}

TEST_CASE("[ReplayGame] - InvalidInputs")
{
    auto config = ReplayConfig();
    ReplayGame parent(config, 1);

    auto child = parent.Branch();
    const auto before = StateOf(*child);

    CHECK_THROWS_AS(child->Process(PlayCardTask(InHand(parent, "CS2_231"))),
                    std::invalid_argument);
    CHECK_THROWS_AS(
        child->Process(SimpleTasks::DamageTask(EntityType::ENEMY_HERO, 1)),
        std::invalid_argument);
    CHECK_THROWS_AS(child->Process(AttackTask(nullptr, nullptr)),
                    std::invalid_argument);
    CHECK_THROWS_AS(child->Process(ChooseTask({})), std::logic_error);
    CHECK_EQ(StateOf(*child), before);
    CHECK_EQ(StateOf(*child->Branch()), before);

    config.skipMulligan = false;

    CHECK_THROWS_AS(ReplayGame(config, 1), std::invalid_argument);

    config.skipMulligan = true;
    config.player1Class = CardClass::NEUTRAL;

    CHECK_THROWS_AS(ReplayGame(config, 1), std::invalid_argument);
}

TEST_CASE("[ReplayGame] - PendingChoices")
{
    auto config = ReplayConfig();
    config.player1Deck.fill(Cards::FindCardByID("LOE_023"));  // Dark Peddler

    ReplayGame parent(config, 7);
    parent.Process(EndTurnTask());
    parent.Process(EndTurnTask());
    parent.Process(PlayCardTask(InHand(parent, "LOE_023")));

    REQUIRE(parent.GetCurrentPlayer()->choice);
    CHECK_THROWS_AS(parent.Branch(), std::logic_error);
    CHECK_THROWS_AS(parent.Process(EndTurnTask()), std::logic_error);
    CHECK_THROWS_AS(parent.Process(ChooseTask({})), std::invalid_argument);

    parent.Process(
        ChooseTask({ parent.GetCurrentPlayer()->choice->choices[0] }));

    REQUIRE_FALSE(parent.GetCurrentPlayer()->choice);

    auto child = parent.Branch();

    CHECK_EQ(StateOf(*child), StateOf(parent));
    CheckIndependent(parent, *child);
}

TEST_CASE("[ReplayGame] - InvalidStates")
{
    auto config = ReplayConfig();
    config.player1Deck.fill(nullptr);
    config.player2Deck.fill(nullptr);

    ReplayGame parent(config, 8);

    for (int i = 0; i < 30 && parent.GetGame().state == State::RUNNING; ++i)
    {
        parent.Process(EndTurnTask());
    }

    REQUIRE_EQ(parent.GetGame().state, State::COMPLETE);
    CHECK_THROWS_AS(parent.Branch(), std::logic_error);
    CHECK_THROWS_AS(parent.Process(EndTurnTask()), std::logic_error);

    ReplayGame unfinished(ReplayConfig(), 8);
    auto* game = unfinished.GetCurrentPlayer()->game;

    game->taskQueue.Enqueue(std::make_unique<EndTurnTask>());
    game->taskQueue.StartEvent();

    // The current event hides the base queue.
    REQUIRE(game->taskQueue.IsEmpty());
    CHECK_FALSE(game->taskQueue.IsIdle());
    CHECK_THROWS_AS(unfinished.Branch(), std::logic_error);
}
