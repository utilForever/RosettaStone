// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Enchants/Attrs/Atk.hpp>
#include <Rosetta/PlayMode/Enchants/Effect.hpp>
#include <Rosetta/PlayMode/Enchants/GenericEffect.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <utility>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[Generic] - AddEnchantment ignores null target")
{
    auto enchantmentCard = TestUtils::GenerateEnchantmentCard("enchantment");
    CHECK_NOTHROW(
        Generic::AddEnchantment(&enchantmentCard, nullptr, nullptr, 0, 0));
}

TEST_CASE("[Generic] - Location play requirements")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Card card;
    card.gameTags[GameTag::CARDTYPE] = std::to_underlying(CardType::LOCATION);
    card.gameTags[GameTag::HEALTH] = 1;
    card.playRequirements.emplace(PlayReq::REQ_WEAPON_EQUIPPED, 0);

    Player* player = game.GetCurrentPlayer();
    Playable* location = Generic::DrawCard(player, &card);

    Generic::PlayCard(player, location);

    CHECK_EQ(player->GetFieldZone()->GetCount(), 0);
    CHECK_EQ(player->GetHandZone()->GetCount(), 1);
}

TEST_CASE("[Generic] - ReplayCard resolves discover choices")
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetCurrentPlayer();
    Generic::ReplayCard(player, Cards::FindCardByID("REV_313"));

    CHECK_FALSE(player->choice);
    CHECK_EQ(player->GetHandZone()->GetCount(), 1);
}

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

TEST_CASE("[Generic] - ChangeEntity transfers ownership")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetPlayer1();
    Playable* oldEntity =
        Entity::GetFromCard(player, Cards::FindCardByID("GAME_005"));
    player->GetHandZone()->Add(oldEntity);
    oldEntity->costManager = std::make_unique<CostManager>();

    const int entityID = oldEntity->GetGameTag(GameTag::ENTITY_ID);
    Generic::ChangeEntity(player, oldEntity, Cards::FindCardByID("CS2_231"),
                          false);

    Playable* newEntity = game.entityList.at(entityID);
    CHECK_NE(newEntity, oldEntity);
    CHECK_EQ(newEntity->zone, player->GetHandZone());
    CHECK_EQ(oldEntity->zone, player->GetSetasideZone());
    CHECK(newEntity->costManager);
    CHECK_FALSE(oldEntity->costManager);

    Generic::ChangeEntity(player, newEntity, Cards::FindCardByID("CS2_091"),
                          false);
    CHECK(dynamic_cast<Weapon*>(game.entityList.at(entityID)));

    newEntity = game.entityList.at(entityID);
    Generic::ChangeEntity(player, newEntity, Cards::FindCardByID("REV_983"),
                          false);
    CHECK(dynamic_cast<Location*>(game.entityList.at(entityID)));
}

TEST_CASE("[Generic] - One-turn attack effect variants")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    auto minionCard = TestUtils::GenerateMinionCard("minion", 2, 3);

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetPlayer1();
    TestUtils::PlayMinionCard(player, &minionCard);
    Minion* minion = (*player->GetFieldZone())[0];

    const auto oneTurnAttack = std::make_shared<GenericEffect<Playable, Atk>>(
        std::make_shared<Atk>(), EffectOperator::ADD, 1);

    oneTurnAttack->ApplyTo(minion, true);
    CHECK_EQ(minion->GetAttack(), 3);
    CHECK_EQ(game.oneTurnEffects.size(), 1u);

    Atk::Effect(EffectOperator::SET, 4)->ApplyTo(minion);
    CHECK_EQ(minion->GetAttack(), 4);
    CHECK(game.oneTurnEffects.empty());

    const auto subtractAura = Atk::Effect(EffectOperator::SUB, 1);

    subtractAura->ApplyAuraTo(minion);
    CHECK_EQ(minion->auraEffects->GetAttack(), -1);
    subtractAura->RemoveAuraFrom(minion);
    CHECK_EQ(minion->auraEffects->GetAttack(), 0);

    const auto setAura = Atk::Effect(EffectOperator::SET, 1);

    setAura->ApplyAuraTo(minion);
    CHECK_EQ(minion->auraEffects->GetAttack(), 1);
    setAura->RemoveAuraFrom(minion);
    CHECK_EQ(minion->auraEffects->GetAttack(), 0);

    minion->SetNativeGameTag(GameTag::ATK, 4);

    Effect subtractAttack(GameTag::ATK, EffectOperator::SUB, 1);
    subtractAttack.ApplyTo(minion);
    subtractAttack.RemoveFrom(minion);
    CHECK_EQ(minion->GetAttack(), 4);

    const auto multiplyAttack = Atk::Effect(EffectOperator::MUL, 2);
    multiplyAttack->ApplyTo(minion);
    CHECK_EQ(minion->GetAttack(), 8);

    minion->auraEffects->SetAttack(2);
    multiplyAttack->ApplyAuraTo(minion);
    CHECK_EQ(minion->auraEffects->GetAttack(), 4);

    minionCard.targetingType = TargetingType::NONE;
    CHECK_FALSE(minion->HasAnyValidPlayTargets(&minionCard));

    minionCard.targetingType = TargetingType::HEROES;
    CHECK(minion->HasAnyValidPlayTargets(&minionCard));

    minion->ActivateTask(PowerType::HONORABLE_KILL);
    oneTurnAttack->ApplyTo(minion, true);
    CHECK_FALSE(game.oneTurnEffects.empty());

    minion->Silence();
    CHECK(game.oneTurnEffects.empty());
}

TEST_CASE("[Generic] - Remove scripted one-turn enchantment early")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    auto minionCard = TestUtils::GenerateMinionCard("minion", 2, 3);
    auto enchantmentCard = TestUtils::GenerateEnchantmentCard("enchantment");

    enchantmentCard.gameTags[GameTag::TAG_ONE_TURN_EFFECT] = 1;
    enchantmentCard.power.AddEnchant(std::make_shared<Enchant>(
        std::make_shared<Effect>(GameTag::ATK, EffectOperator::ADD, 0), true,
        true));
    enchantmentCard.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetPlayer1();
    TestUtils::PlayMinionCard(player, &minionCard);

    Minion* minion = (*player->GetFieldZone())[0];
    Generic::AddEnchantment(&enchantmentCard, minion, minion, 3);

    const Effect unrelatedEffect(GameTag::ATK, EffectOperator::ADD, 0);
    unrelatedEffect.ApplyTo(player->GetHero(), true);

    CHECK_EQ(minion->appliedEnchantments.size(), 1u);
    CHECK_EQ(minion->GetAttack(), 5);
    CHECK_EQ(game.oneTurnEffects.size(), 2u);

    RemoveEnchantmentTask task;
    task.SetPlayer(player);
    task.SetSource(minion->appliedEnchantments[0].get());
    CHECK_EQ(task.Run(), TaskStatus::COMPLETE);

    CHECK_EQ(minion->GetAttack(), 2);
    CHECK_EQ(game.oneTurnEffects.size(), 1u);
    CHECK_EQ(game.oneTurnEffects[0].first, player->GetHero());

    game.MainCleanUp();
    CHECK(game.oneTurnEffects.empty());
    CHECK_EQ(minion->GetAttack(), 2);
}
