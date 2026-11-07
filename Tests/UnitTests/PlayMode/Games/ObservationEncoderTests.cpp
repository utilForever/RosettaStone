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
    SUBCASE("Unsupported mechanics in hidden cards remain private")
    {
        for (const auto* id : { "DRG_255", "ULD_266" })
        {
            Draw(first->GetCurrentPlayer()->opponent, "CS2_231");
            Draw(opponent, id);

            for (auto* owner : { player, opponent })
            {
                auto* deck = owner->GetDeckZone();

                owner->GetSetasideZone()->Add(deck->Remove(deck->GetTopCard()));
                AddToZone(owner, id, deck);
            }
        }
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

TEST_CASE("[Observation] - Runtime values and zero padding follow the schema")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();

    game->Process(player, PlayCardTask(Draw(player, "CS2_182")));
    game->Process(player, PlayCardTask(Draw(player, "CS2_106")));
    game->Process(player, HeroPowerTask(player->opponent->GetHero()));

    auto* minion = (*player->GetFieldZone())[0];
    minion->SetAttack(7);
    minion->SetBaseHealth(9);
    minion->SetDamage(2);
    minion->SetSpellPower(3);
    minion->SetNumAttacksThisTurn(2);
    minion->SetAttackableByRush(true);

    for (const auto tag :
         { GameTag::EXHAUSTED, GameTag::FROZEN, GameTag::IMMUNE, GameTag::TAUNT,
           GameTag::DIVINE_SHIELD, GameTag::STEALTH, GameTag::WINDFURY,
           GameTag::CHARGE, GameTag::RUSH, GameTag::POISONOUS,
           GameTag::LIFESTEAL, GameTag::SILENCED, GameTag::CANT_ATTACK,
           GameTag::CANNOT_ATTACK_HEROES, GameTag::MEGA_WINDFURY })
    {
        minion->SetGameTag(tag, 1);
    }

    player->GetHero()->SetArmor(6);
    player->GetHero()->SetAttack(2);
    player->GetHero()->fatigue = 4;
    player->GetWeapon().SetDurability(1);
    player->GetWeapon().SetGameTag(GameTag::LIFESTEAL, 1);
    player->GetHeroPower().SetCost(1);
    player->GetHeroPower().SetExhausted(true);
    player->SetTotalMana(9);
    player->SetUsedMana(2);
    player->SetTemporaryMana(3);
    player->SetOverloadLocked(1);
    player->SetOverloadOwed(2);
    player->SetNumCardsPlayedThisTurn(5);
    player->playerAuraEffects.SetValue(GameTag::CHOOSE_BOTH, 1);

    const auto handSlot = player->GetHandZone()->GetCount();
    auto* spell = Draw(player, "CS2_029");

    spell->SetCost(2);

    const auto observation = EncodeObservation(*game);
    const auto& board = observation.board[Schema::SELF][0];

    CHECK_EQ(board[Schema::CARD_ID], minion->card->dbfID);
    CHECK_EQ(board[Schema::COST], 0);
    CHECK_EQ(board[Schema::ATTACK], 7);
    CHECK_EQ(board[Schema::HEALTH], 7);
    CHECK_EQ(board[Schema::MAX_HEALTH], 9);
    CHECK_EQ(board[Schema::SPELL_POWER], 3);
    CHECK_EQ(board[Schema::ATTACKS_THIS_TURN], 2);
    CHECK_EQ(board[Schema::FLAGS], (1 << 16) - 1);
    CHECK_EQ(observation.heroes[0][Schema::ARMOR], 6);
    CHECK_EQ(observation.heroes[0][Schema::ATTACK], 5);
    CHECK((observation.heroes[0][Schema::FLAGS] & Schema::LIFESTEAL) != 0);
    CHECK_EQ(observation.weapons[0][Schema::ATTACK], 3);
    CHECK_EQ(observation.weapons[0][Schema::DURABILITY], 1);
    CHECK_EQ(observation.heroPowers[0][Schema::COST], 1);
    CHECK((observation.heroPowers[0][Schema::FLAGS] & Schema::EXHAUSTED) != 0);

    const Schema::Player resources{ 9,
                                    2,
                                    3,
                                    1,
                                    2,
                                    player->GetHandZone()->GetCount(),
                                    player->GetDeckZone()->GetCount(),
                                    0,
                                    4,
                                    5,
                                    1 };

    CHECK(observation.players[0] == resources);
    CHECK_EQ(observation.turn[Schema::TURN_NUMBER], game->GetTurn());
    CHECK_EQ(observation.turn[Schema::DECISION], Schema::MAIN_ACTION);
    CHECK_EQ(observation.hand[handSlot][Schema::COST], 2);

    for (std::size_t field = Schema::ATTACK; field <= Schema::ATTACKS_THIS_TURN;
         ++field)
    {
        CHECK_EQ(observation.hand[handSlot][field], 0);
        CHECK_EQ(observation.heroPowers[0][field], 0);
    }

    CHECK(observation.board[0][1] == Schema::Card{});
    CHECK(observation.weapons[1] == Schema::Card{});
    CHECK(observation.hand.back() == Schema::Card{});
    CHECK(observation.choices == decltype(observation.choices){});
    CHECK(observation.secrets == decltype(observation.secrets){});
}

TEST_CASE(
    "[Observation] - Changing actor selects the relative public and private "
    "rows")
{
    auto game = ObservationGame();
    auto* first = game->GetCurrentPlayer();
    auto* second = first->opponent;

    AddToZone(first, "EX1_287", first->GetSecretZone());
    AddToZone(second, "EX1_289", second->GetSecretZone());
    Draw(first, "EX1_160");  // Power of the Wild
    Draw(second, "CS2_029");

    game->Process(first, PlayCardTask(Draw(first, "CS2_182")));
    game->Process(first, PlayCardTask(Draw(first, "CS2_120")));

    const auto firstView = EncodeObservation(*game);

    game->SetCurrentPlayer(PlayerType::PLAYER2);

    const auto secondView = EncodeObservation(*game);

    CHECK(secondView.players[0] == firstView.players[1]);
    CHECK(secondView.players[1] == firstView.players[0]);
    CHECK(secondView.heroes[0] == firstView.heroes[1]);
    CHECK(secondView.heroPowers[0] == firstView.heroPowers[1]);
    CHECK(secondView.board[1] == firstView.board[0]);
    CHECK_EQ(
        secondView.hand[second->GetHandZone()->GetCount() - 1][Schema::CARD_ID],
        Cards::FindCardByID("CS2_029")->dbfID);
    CHECK_EQ(firstView.secrets[0], Cards::FindCardByID("EX1_287")->dbfID);
    CHECK_EQ(secondView.secrets[0], Cards::FindCardByID("EX1_289")->dbfID);
    CHECK(secondView.chooseOne == decltype(secondView.chooseOne){});

    const auto chooseSlot = first->GetHandZone()->GetCount() - 1;
    const auto* chooseCard = Cards::FindCardByID("EX1_160");

    REQUIRE_EQ(chooseCard->chooseCardIDs.size(), 2);

    for (std::size_t option = 0; option < 2; ++option)
    {
        CHECK_EQ(firstView.chooseOne[chooseSlot][option],
                 Cards::FindCardByID(chooseCard->chooseCardIDs[option])->dbfID);
    }
}

TEST_CASE(
    "[Observation] - General choices expose only the offered cards in order")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();
    auto* minion = AddToZone(player, "CS2_182", player->GetSetasideZone());
    auto* spell = AddToZone(player, "CS2_029", player->GetSetasideZone());

    minion->SetCost(1);
    player->choice = std::make_unique<Choice>(player);

    auto& choice = *player->choice;
    choice.choiceType = ChoiceType::GENERAL;
    choice.choiceAction = ChoiceAction::HAND;
    choice.choices = { spell->GetGameTag(GameTag::ENTITY_ID),
                       minion->GetGameTag(GameTag::ENTITY_ID) };

    const auto observation = EncodeObservation(*game);

    CHECK_EQ(observation.turn[Schema::DECISION], Schema::GENERAL_CHOICE);
    CHECK_EQ(observation.choices[0][Schema::CARD_ID], spell->card->dbfID);
    CHECK_EQ(observation.choices[1][Schema::CARD_ID], minion->card->dbfID);
    CHECK_EQ(observation.choices[1][Schema::COST], 1);
    CHECK_EQ(observation.choices[1][Schema::ATTACK], 4);
    CHECK(observation.choices[2] == Schema::Card{});

    choice.cardSets = { Cards::FindCardByID("CS2_120") };

    CHECK(EncodeObservation(*game) == observation);

    std::ranges::reverse(choice.choices);

    CHECK_FALSE(EncodeObservation(*game) == observation);
}

TEST_CASE(
    "[Observation] - Played sidequests are rejected from both perspectives")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();

    REQUIRE_NOTHROW(EncodeObservation(*game));

    auto* sidequest = Draw(player, "DRG_255");  // Toxic Reinforcements

    game->Process(player, PlayCardTask(sidequest));

    REQUIRE_EQ(sidequest->GetZoneType(), ZoneType::SECRET);
    REQUIRE_EQ(player->GetSecretZone()->quest, nullptr);

    for (int progress = 0; progress <= 1; ++progress)
    {
        game->SetCurrentPlayer(player->playerType);

        if (progress == 1)
        {
            game->Process(player, HeroPowerTask(player->opponent->GetHero()));
        }

        REQUIRE_EQ(sidequest->GetGameTag(GameTag::QUEST_PROGRESS), progress);

        for (const auto seat : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
        {
            game->SetCurrentPlayer(seat);
            CHECK_THROWS_AS(EncodeObservation(*game), std::invalid_argument);
        }
    }
}

TEST_CASE("[Observation] - Reborn on different public slots is rejected")
{
    std::array games{ ObservationGame(), ObservationGame() };

    for (const auto& game : games)
    {
        auto* player = game->GetCurrentPlayer();

        game->Process(player, PlayCardTask(Draw(player, "CS2_182")));
        game->Process(player, PlayCardTask(Draw(player, "CS2_182")));

        REQUIRE_EQ(player->GetFieldZone()->GetCount(), 2);
        REQUIRE_NOTHROW(EncodeObservation(*game));
    }

    CHECK(EncodeObservation(*games[0]) == EncodeObservation(*games[1]));

    for (int slot = 0; slot < 2; ++slot)
    {
        auto& game = *games[slot];
        auto* player = game.GetCurrentPlayer();
        auto* board = player->GetFieldZone();

        game.Process(player,
                     PlayCardTask(Draw(player, "ULD_265"), (*board)[slot]));

        REQUIRE((*board)[slot]->HasReborn());
        REQUIRE_FALSE((*board)[1 - slot]->HasReborn());

        for (const auto seat : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
        {
            game.SetCurrentPlayer(seat);
            CHECK_THROWS_AS(EncodeObservation(game), std::invalid_argument);
        }
    }
}

TEST_CASE("[Observation] - Unsupported decision boundaries are rejected")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();

    SUBCASE("Terminal")
    {
        game->state = State::COMPLETE;
    }
    SUBCASE("Mulligan")
    {
        game->step = Step::BEGIN_MULLIGAN;
    }
    SUBCASE("Open event")
    {
        game->taskQueue.StartEvent();
    }
    SUBCASE("Pending summon")
    {
        game->summonedMinions.push_back(nullptr);
    }
    SUBCASE("Pending death")
    {
        game->deadMinions.emplace(1, nullptr);
    }
    SUBCASE("Pending reborn")
    {
        game->rebornMinions.emplace(1, nullptr);
    }
    SUBCASE("Opponent choice")
    {
        player->opponent->choice = std::make_unique<Choice>(player->opponent);
    }
    SUBCASE("Public quest")
    {
        AddToZone(player, "UNG_028", player->GetSecretZone());
    }
    SUBCASE("Sidequest in the actor's hand")
    {
        Draw(player, "DRG_255");
    }
    SUBCASE("Reborn in the actor's hand")
    {
        Draw(player, "ULD_266");
    }
    SUBCASE("Dormant minion")
    {
        auto* minion = AddToZone(player, "CS2_182", player->GetFieldZone());
        minion->SetGameTag(GameTag::DORMANT, 1);
    }
    SUBCASE("Untouchable minion")
    {
        auto* minion = AddToZone(player, "CS2_182", player->GetFieldZone());
        minion->SetGameTag(GameTag::UNTOUCHABLE, 1);
    }
    SUBCASE("Location")
    {
        AddToZone(player, "REV_290", player->GetFieldZone());
    }
    SUBCASE("Expanded actor hand exceeds schema capacity")
    {
        player->GetHandZone()->Expand(11);

        while (player->GetHandZone()->GetCount() < 11)
        {
            Draw(player, "CS2_231");
        }
    }
    SUBCASE("Expanded opponent hand exceeds schema capacity")
    {
        auto* opponent = player->opponent;
        opponent->GetHandZone()->Expand(11);

        while (opponent->GetHandZone()->GetCount() < 11)
        {
            Draw(opponent, "CS2_231");
        }
    }

    CHECK_THROWS_AS(EncodeObservation(*game), std::invalid_argument);
}

TEST_CASE("[Observation] - Unsupported or invalid choices are rejected")
{
    auto game = ObservationGame();
    auto* player = game->GetCurrentPlayer();
    auto* offer = AddToZone(player, "CS2_182", player->GetSetasideZone());

    player->choice = std::make_unique<Choice>(player);

    auto& choice = *player->choice;
    choice.choiceType = ChoiceType::GENERAL;
    choice.choiceAction = ChoiceAction::HAND;
    choice.choices = { offer->GetGameTag(GameTag::ENTITY_ID) };

    SUBCASE("Empty offer")
    {
        choice.choices.clear();
    }
    SUBCASE("Too many offers")
    {
        choice.choices.resize(5, choice.choices[0]);
    }
    SUBCASE("Unknown entity")
    {
        choice.choices[0] = -12345;
    }
    SUBCASE("Mulligan choice")
    {
        choice.choiceType = ChoiceType::MULLIGAN;
    }
    SUBCASE("Unsupported action")
    {
        choice.choiceAction = ChoiceAction::DREDGE;
    }
    SUBCASE("Wrong owner")
    {
        choice.player = player->opponent;
    }
    SUBCASE("Nested choice")
    {
        choice.nextChoice = std::make_unique<Choice>(player);
    }
    SUBCASE("Follow-up depth")
    {
        choice.depth = 2;
    }
    SUBCASE("Stack context")
    {
        choice.entityStack.push_back(choice.choices[0]);
    }
    SUBCASE("Source context")
    {
        choice.source = player->GetHero();
    }

    const auto entityCount = game->entityList.size();

    CHECK_THROWS_AS(EncodeObservation(*game), std::invalid_argument);
    CHECK_EQ(game->entityList.size(), entityCount);
}

TEST_CASE("[Observation] - Invalid visible metadata is rejected")
{
    auto game = ObservationGame();
    auto* entity = game->GetCurrentPlayer()->GetHandZone()->GetAll()[0];
    auto* original = entity->card;
    Card invalid = *original;

    entity->card = &invalid;

    SUBCASE("Nonpositive DBF ID")
    {
        invalid.dbfID = 0;
    }
    SUBCASE("Unknown DBF ID")
    {
        invalid.dbfID = 2147483647;
    }
    SUBCASE("Unknown DBF ID and empty string ID")
    {
        invalid.dbfID = 2147483647;
        invalid.id.clear();
    }
    SUBCASE("Unknown Choose One ID")
    {
        invalid.chooseCardIDs = { "OBSERVATION_UNKNOWN_CARD" };
    }
    SUBCASE("Choose One capacity overflow")
    {
        invalid.chooseCardIDs.assign(5, "CS2_231");
    }

    CHECK_THROWS_AS(EncodeObservation(*game), std::invalid_argument);

    entity->card = original;
}
