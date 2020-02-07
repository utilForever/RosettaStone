// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [DAL_350] Crystal Power - COST:1
// - Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 2 damage to a minion;
//       or Restore 5 Health.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST(DruidDalaranTest, DAL_350_CrystalPower)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(10);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Power"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Power"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero(), 2));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3, 1));
    EXPECT_EQ(opField[0]->GetHealth(), 5);
}

// [DAL_351] Blessing of the Ancients - COST:3
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> Give your minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54128
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(DruidDalaranTest, DAL_351_BlessingOfTheAncients)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_351"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    EXPECT_EQ(curField[0]->GetAttack(), 1);
    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(curField[1]->GetAttack(), 1);
    EXPECT_EQ(curField[1]->GetHealth(), 1);
    EXPECT_EQ(curField[2]->GetAttack(), 1);
    EXPECT_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(curHand.GetCount(), 1);
    EXPECT_EQ(curHand[0]->card->id, "DAL_351ts");
    EXPECT_EQ(curField[0]->GetAttack(), 2);
    EXPECT_EQ(curField[0]->GetHealth(), 2);
    EXPECT_EQ(curField[1]->GetAttack(), 2);
    EXPECT_EQ(curField[1]->GetHealth(), 2);
    EXPECT_EQ(curField[2]->GetAttack(), 2);
    EXPECT_EQ(curField[2]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    EXPECT_EQ(curHand.GetCount(), 0);
    EXPECT_EQ(curField[0]->GetAttack(), 3);
    EXPECT_EQ(curField[0]->GetHealth(), 3);
    EXPECT_EQ(curField[1]->GetAttack(), 3);
    EXPECT_EQ(curField[1]->GetHealth(), 3);
    EXPECT_EQ(curField[2]->GetAttack(), 3);
    EXPECT_EQ(curField[2]->GetHealth(), 3);
}

// ----------------------------------------- MINION - DRUID
// [DAL_354] Acornbearer - COST:1 [ATK:2/HP:1]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add two 1/1 Squirrels to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(DruidDalaranTest, DAL_354_Acornbearer)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());
    
    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Acornbearer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curField[0]->GetAttack(), 2);
    EXPECT_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

	game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));

    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    EXPECT_EQ(curHand[4]->card->name, "Squirrel");
    EXPECT_EQ(curHand[5]->card->name, "Squirrel");
}

// ----------------------------------------- MINION - DRUID
// [DAL_355] Lifeweaver - COST:3 [ATK:2/HP:5]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you restore Health,
//       add a random Druid spell to your hand.
// --------------------------------------------------------
TEST(DruidDalaranTest, DAL_355_Lifeweaver)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(10);
    opPlayer->GetHero()->SetDamage(10);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lifeweaver"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Healing Touch"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card3, opPlayer->GetHero()));

    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 28);
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 22);
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    EXPECT_EQ(curHand[4]->card->GetCardClass(), CardClass::DRUID);
    // EXPECT_EQ(curHand[5]->card->GetCardClass(), CardClass::DRUID);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));

    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}
// ------------------------------------------ SPELL - DRUID
// [DAL_733] Dreamway Guardians - COST:2
// - Faction: Neutral, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Summon two 1/2 Dryads with <b>Lifesteal</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST(DruidDalaranTest, DAL_733_DreamwayGuardians)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(1);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dreamway Guardians"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dreamway Guardians"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dreamway Guardians"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dreamway Guardians"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(curField.GetCount(), 2);
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    EXPECT_EQ(curField.GetCount(), 4);
    game.Process(curPlayer, PlayCardTask::Spell(card3));
    EXPECT_EQ(curField.GetCount(), 6);
    game.Process(curPlayer, PlayCardTask::Spell(card4));
    EXPECT_EQ(curField.GetCount(), 7);
    EXPECT_EQ(curField[0]->card->name, "Crystal Dryad");
    EXPECT_EQ(curField[1]->card->name, "Crystal Dryad");
    EXPECT_EQ(curField[0]->GetAttack(), 1);
    EXPECT_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, curField[0]));

    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_078] Traveling Healer - COST:4 [ATK:3/HP:2]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b> <b>Battlecry:</b> Restore 3 Health.
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST(NeutralDalaranTest, DAL_078_TravellingHealer)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(3);

    auto& curField = *(curPlayer->GetFieldZone());
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Traveling Healer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    EXPECT_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curField[0]->HasDivineShield(), true);

    game.Process(opPlayer, PlayCardTask::Weapon(card2));
    game.Process(opPlayer, AttackTask(opHero, curField[0]));

    EXPECT_EQ(curField[0]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_760] Burly Shovelfist - COST:9 [ATK:9/HP:9]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST(NeutralDalaranTest, DAL_760_BurlyShovelfist)
{
    // Do nothing
}