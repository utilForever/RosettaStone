// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [DAL_256] The Forest's Aid - COST:8
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Twinspell</b> Summon five 2/2 Treants.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 52821
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DAL_256 : The Forest's Aid")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_256"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "DAL_256ts");
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Treant");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Treant");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[3]->card->name, "Treant");
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 2);
    CHECK_EQ(curField[4]->card->name, "Treant");
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Treant");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->card->name, "Treant");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[3]->card->name, "Treant");
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 2);
    CHECK_EQ(curField[4]->card->name, "Treant");
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);
}

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
TEST_CASE("[Druid : Spell] - DAL_350 : Crystal Power")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3, 1));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ------------------------------------------ SPELL - DRUID
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
TEST_CASE("[Druid : Spell] - DAL_351 : Blessing of the Ancients")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "DAL_351ts");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// ------------------------------------------ SPELL - DRUID
// [DAL_352] Crystalsong Portal - COST:2
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Discover</b> a Druid minion.
//       If your hand has no minions, keep all 3.
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - DAL_352 : Crystalsong Portal")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crystalsong Portal"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crystalsong Portal"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::DRUID);
    CHECK_EQ(curHand[2]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[2]->card->GetCardClass(), CardClass::DRUID);
    CHECK_EQ(curHand[3]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[3]->card->GetCardClass(), CardClass::DRUID);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetCardClass(), CardClass::DRUID);
    }
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
TEST_CASE("[Druid : Minion] - DAL_354 : Acornbearer")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Squirrel");
    CHECK_EQ(curHand[5]->card->name, "Squirrel");
}

// ----------------------------------------- MINION - DRUID
// [DAL_355] Lifeweaver - COST:3 [ATK:2/HP:5]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you restore Health,
//       add a random Druid spell to your hand.
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DAL_355 : Lifeweaver")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curHand[5]->card->GetCardClass(), CardClass::DRUID);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curHand[5]->card->GetCardClass(), CardClass::DRUID);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// ----------------------------------------- MINION - DRUID
// [DAL_357] Lucentbark - COST:8 [ATK:4/HP:8]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Go dormant.
//       Restore 5 Health to awaken this minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DAL_357 : Lucentbark")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lucentbark"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Healing Touch"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->name, "Lucentbark");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField[0]->card->name, "Spirit of Lucentbark");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(curField[0]->card->name, "Spirit of Lucentbark");
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[0]->card->name, "Lucentbark");
}

// ----------------------------------------- MINION - DRUID
// [DAL_732] Keeper Stalladris - COST:2 [ATK:2/HP:3]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: After you cast a <b>Choose One</b> spell,
//       add copies of both choices to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DAL_732 : Keeper Stalladris")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(10);

    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Keeper Stalladris"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wrath"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Druid of the Claw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, PlayCardTask::Minion(card4, 1));
    CHECK_EQ(opHand.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1, 1));
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[1]->card->id, "EX1_154a");
    CHECK_EQ(opHand[2]->card->id, "EX1_154b");
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
TEST_CASE("[Druid : Spell] - DAL_733 : Dreamway Guardians")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Crystal Dryad");
    CHECK_EQ(curField[1]->card->name, "Crystal Dryad");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasLifesteal(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ----------------------------------------- MINION - DRUID
// [DAL_799] Crystal Stag - COST:5 [ATK:4/HP:4]
// - Race: Beast, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b>. <b>Battlecry:</b> If you've restored
//       5 Health this game, summon a copy of this.
//       @ <i>({0} left!)</i>@ <i>(Ready!)</i>
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// - PLAYER_TAG_THRESHOLD_TAG_ID = 958
// - PLAYER_TAG_THRESHOLD_VALUE = 5
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - DAL_799 : Crystal Stag")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(10);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Stag"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crystal Stag"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Healing Touch"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
}

// ----------------------------------------- SPELL - HUNTER
// [DAL_371] Marked Shot - COST:4
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Deal 4 damage to a minion. <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_371 : Marked Shot")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Marked Shot"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK(opPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::PALADIN));
    }
}

// ---------------------------------------- MINION - HUNTER
// [DAL_372] Arcane Fletcher - COST:4 [ATK:3/HP:3]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Whenever you play a 1-Cost minion,
//       draw a spell from your deck.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_372 : Arcane Fletcher")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Marked Shot");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Fletcher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Fletcher"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curDeck.GetCount(), 24);
    CHECK_EQ(curHand[4]->card->name, "Marked Shot");
    CHECK_EQ(curHand[5]->card->name, "Marked Shot");
}

// ----------------------------------------- SPELL - HUNTER
// [DAL_373] Rapid Fire - COST:1
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> Deal 1 damage.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54143
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_373 : Rapid Fire")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_373"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->id, "DAL_373ts");
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[4], opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// ---------------------------------------- MINION - HUNTER
// [DAL_376] Oblivitron - COST:6 [ATK:3/HP:4]
// - Race: Mechanical, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a Mech from your hand
//       and trigger its <b>Deathrattle</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DAL_376 : Oblivitron")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ursatron");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oblivitron"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand[3]->card->name, card2->card->name);
    CHECK_EQ(curHand[4]->card->name, "Ursatron");
}

// ----------------------------------------- SPELL - HUNTER
// [DAL_377] Nine Lives - COST:3
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Discover</b> a friendly <b>Deathrattle</b> minion that
//       died this game. Also trigger its <b>Deathrattle</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_377 : Nine Lives")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nine Lives"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Safeguard"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice == nullptr);
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Vault Safe");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    CHECK_EQ(cards.size(), 1u);
    CHECK_EQ(cards[0]->name, "Safeguard");

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Safeguard");
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Vault Safe");
}

// ----------------------------------------- SPELL - HUNTER
// [DAL_378] Unleash the Beast - COST:6
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Twinspell</b> Summon a 5/5 Wyvern with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54145
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_378 : Unleash the Beast")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_378"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->id, "DAL_378ts");
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ---------------------------------------- MINION - HUNTER
// [DAL_379] Vereesa Windrunner - COST:7 [ATK:5/HP:6]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip Thori'dal, the Stars' Fury.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DAL_379 : Vereesa Windrunner")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto curHero = curPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vereesa Windrunner"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero->HasWeapon(), true);
    CHECK_EQ(curHero->weapon->card->name, "Thori'dal, the Stars' Fury");
    CHECK_EQ(curHero->GetSpellPower(), 0);

    game.Process(curPlayer, AttackTask(curHero, opPlayer->GetHero()));
    CHECK_EQ(curHero->GetSpellPower(), 2);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero->GetSpellPower(), 0);
}

// ---------------------------------------- MINION - HUNTER
// [DAL_587] Shimmerfly - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: Dalaran, Rarity: rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a random Hunter spell to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DAL_587 : Shimmerfly")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shimmerfly"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::HUNTER);
}

// ----------------------------------------- SPELL - HUNTER
// [DAL_589] Hunting Party - COST:5
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Copy all Beasts in your hand.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DAL_589 : Hunting Party")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hunting Party"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[3]->card->name, card2->card->name);
    CHECK_EQ(curHand[4]->card->name, card4->card->name);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 4);
}

// ---------------------------------------- MINION - HUNTER
// [DAL_604] Ursatron - COST:3 [ATK:3/HP:3]
// - Race: Mechanical, Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a Mech from your deck.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - DAL_604 : Ursatron")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Harvest Golem");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ursatron"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ursatron"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(card1->isDestroyed, true);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Harvest Golem");

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(card2->isDestroyed, true);
    CHECK_EQ(curHand.GetCount(), 5);
}

// ------------------------------------------ MINION - MAGE
// [DAL_163] Messenger Raven - COST:3 [ATK:3/HP:2]
// - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a Mage minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_163 : Messenger Raven")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Messenger Raven"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetCardClass(), CardClass::MAGE);
    }
}

// ------------------------------------------- SPELL - MAGE
// [DAL_177] Conjurer's Calling - COST:3
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Twinspell</b> Destroy a minion.
//       Summon 2 minions of the same Cost to replace it.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 52637
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DAL_177 : Conjurer's Calling")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_177"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "DAL_177ts");
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetCost(), 9);
    CHECK_EQ(curField[1]->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card3));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetCost(), 3);
    CHECK_EQ(opField[1]->GetCost(), 3);
}

// ------------------------------------------ MINION - MAGE
// [DAL_182] Magic Dart Frog - COST:2 [ATK:1/HP:3]
// - Race: Beast, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: After you cast a spell, deal 1 damage to a random enemy minion.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_182 : Magic Dart Frog")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magic Dart Frog"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ------------------------------------------ MINION - MAGE
// [DAL_575] Khadgar - COST:2 [ATK:2/HP:2]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Your cards that summon minions summon twice as many.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_575 : Khadgar")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Khadgar"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Harvest Golem"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Damaged Golem");
    CHECK_EQ(curField[1]->card->name, "Damaged Golem");
    CHECK_EQ(curField[2]->card->name, "Khadgar");
}

// ------------------------------------------ MINION - MAGE
// [DAL_576] Kirin Tor Tricaster - COST:4 [ATK:3/HP:3]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +3</b> Your spells cost (1) more.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 3
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_576 : Kirin Tor Tricaster")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kirin Tor Tricaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 3);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 21);
}

// ------------------------------------------- SPELL - MAGE
// [DAL_577] Ray of Frost - COST:1
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> <b>Freeze</b> a minion.
//       If it's already <b>Frozen</b>, deal 2 damage to it.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54193
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DAL_577 : Ray of Frost")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DAL_577"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DAL_577"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(card1->GetGameTag(GameTag::TWINSPELL), 1);

    CHECK_EQ(curField[0]->IsFrozen(), false);
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[0]->GetDamage(), 0);

    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[2]->GetGameTag(GameTag::TWINSPELL), 0);
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[0]->GetDamage(), 2);

    CHECK_EQ(opHand.GetCount(), 3);
    CHECK_EQ(opHand[2]->GetGameTag(GameTag::TWINSPELL), 0);
    game.Process(opPlayer, PlayCardTask::SpellTarget(opHand[1], card3));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[0]->GetDamage(), 4);

    CHECK_EQ(opHand.GetCount(), 2);
    game.Process(opPlayer, PlayCardTask::SpellTarget(opHand[1], card3));
    CHECK_EQ(card3->isDestroyed, true);
    CHECK_EQ(opHand.GetCount(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [DAL_578] Power of Creation - COST:8
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Discover</b> a 6-Cost minion. Summon two copies of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DAL_578 : Power of Creation")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Power of Creation"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetCost(), 6);
    }

    Generic::ChoicePick(curPlayer, 24);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetCost(), 6);
    CHECK_EQ(curField[1]->GetCost(), 6);
    CHECK_EQ(curField[0]->card->name, curField[1]->card->name);
}

// ------------------------------------------ MINION - MAGE
// [DAL_603] Mana Cyclone - COST:2 [ATK:2/HP:2]
// - Race: Elemental, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> For each spell you've cast this turn,
//       add a random Mage spell to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_603 : Mana Cyclone")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Cyclone"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Image"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Missiles"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Explosion"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Spell(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::MAGE);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::MAGE);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[2]->card->GetCardClass(), CardClass::MAGE);
    CHECK_EQ(curHand[2]->card->GetCardType(), CardType::SPELL);
}

// ------------------------------------------- SPELL - MAGE
// [DAL_608] Magic Trick - COST:1
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Discover</b> a spell that costs (3) or less.
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - DAL_608 : Magic Trick")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magic Trick"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::MAGE));
        CHECK_LE(card->GetCost(), 3);
    }
}

// ------------------------------------------ MINION - MAGE
// [DAL_609] Kalecgos - COST:10 [ATK:4/HP:12]
// - Race: Dragon, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Your first spell each turn costs (0).
//       <b>Battlecry:</b> <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - AURA = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - DAL_609 : Kalecgos")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kalecgos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::MAGE));
    }

    Generic::ChoicePick(curPlayer, 26);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(curHand[6]->GetCost(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(card3->GetCost(), 4);
}

// ---------------------------------------- SPELL - PALADIN
// [DAL_141] Desperate Measures - COST:1
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Twinspell</b> Cast a random Paladin <b>Secret</b>.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54129
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DAL_141 : Desperate Measures")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_141"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    CHECK_EQ(curSecret.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "DAL_141ts");
    CHECK_EQ(curSecret.GetCount(), 2);
    CHECK_NE(curSecret[0]->card->id, curSecret[1]->card->id);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curSecret.GetCount(), 3);
    CHECK_NE(curSecret[0]->card->id, curSecret[1]->card->id);
    CHECK_NE(curSecret[0]->card->id, curSecret[2]->card->id);
    CHECK_NE(curSecret[1]->card->id, curSecret[2]->card->id);
}

// --------------------------------------- MINION - PALADIN
// [DAL_146] Bronze Herald - COST:3 [ATK:3/HP:2]
// - Race: Dragon, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add two 4/4 Dragons to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DAL_146 : Bronze Herald")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curHand[4]->card->name, "Bronze Dragon");
    CHECK_EQ(curHand[5]->card->name, "Bronze Dragon");
}

// --------------------------------------- MINION - PALADIN
// [DAL_147] Dragon Speaker - COST:5 [ATK:3/HP:5]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give all Dragons in your hand +3/+3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DAL_147 : Dragon Speaker")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dragon Speaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Herald"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card5)->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card5)->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 7);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 15);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card5)->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card5)->GetHealth(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [DAL_568] Lightforged Blessing - COST:2
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> Give a friendly minion <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 54189
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DAL_568 : Lightforged Blessing")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(15);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_568"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasLifesteal(), false);
    CHECK_EQ(curField[1]->HasLifesteal(), false);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->id, "DAL_568ts");
    CHECK_EQ(curField[0]->HasLifesteal(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[4], card3));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curField[1]->HasLifesteal(), true);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 18);
}

// ---------------------------------------- SPELL - PALADIN
// [DAL_570] Never Surrender! - COST:1
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When your opponent casts a spell,
//       give your minions +2 Health.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DAL_570 : Never Surrender!")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Never Surrender!"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightforged Blessing"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sen'jin Shieldmasta"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card3));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- WEAPON - PALADIN
// [DAL_571] Mysterious Blade - COST:2 [ATK:2/HP:0]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a
//       <b>Secret</b>, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - DAL_571 : Mysterious Blade")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mysterious Blade"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mysterious Blade"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Never Surrender!"));

    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// --------------------------------------- MINION - PALADIN
// [DAL_573] Commander Rhyssa - COST:3 [ATK:4/HP:3]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Your <b>Secrets</b> trigger twice.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DAL_573 : Commander Rhyssa")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curSecret = *(curPlayer->GetSecretZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Commander Rhyssa"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card4, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Defender");
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - PALADIN
// [DAL_581] Nozari - COST:10 [ATK:4/HP:12]
// - Race: Dragon, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore both heroes to full Health.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - DAL_581 : Nozari")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nozari"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ---------------------------------------- SPELL - PALADIN
// [DAL_727] Call to Adventure - COST:3
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Draw the lowest Cost minion from your deck. Give it +2/+2.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DAL_727 : Call to Adventure")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player1Deck[i + 1] = Cards::FindCardByName("Never Surrender!");
        config.player1Deck[i + 2] = Cards::FindCardByName("Nozari");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Call to Adventure"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Wisp");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->GetHealth(), 3);
}

// ---------------------------------------- SPELL - PALADIN
// [DAL_731] Duel! - COST:5
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Summon a minion from each player's deck. They fight!
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - DAL_731 : Duel!")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Ysera");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 26);
    CHECK_EQ(opPlayer->GetDeckZone()->GetCount(), 26);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Duel!"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 25);
    CHECK_EQ(opField[0]->GetHealth(), 8);
    CHECK_EQ(opPlayer->GetDeckZone()->GetCount(), 25);
}

// ----------------------------------------- SPELL - PRIEST
// [DAL_011] Lazul's Scheme - COST:0
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Reduce the Attack of an enemy minion by
//       @ until your next turn. <i>(Upgrades each turn!)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_1 = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DAL_011 : Lazul's Scheme")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lazul's Scheme"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetAttack(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[0]->GetAttack(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[0]->GetAttack(), 4);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_030] Shadowy Figure - COST:2 [ATK:2/HP:2]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform into a 2/2 copy of
//       a friendly <b>Deathrattle</b> minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_DEATHRATTLE = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DAL_030 : Shadowy Figure")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowy Figure"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Loot Hoarder");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->HasDeathrattle(), true);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_039] Convincing Infiltrator - COST:5 [ATK:2/HP:6]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Destroy a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DAL_039 : Convincing Infiltrator")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Convincing Infiltrator"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 1);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_040] Hench-Clan Shadequill - COST:4 [ATK:4/HP:7]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Restore 5 Health to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DAL_040 : Hench-Clan Shadequill")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(15);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Shadequill"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
}

// ----------------------------------------- SPELL - PRIEST
// [DAL_065] Unsleeping Soul - COST:4
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Silence</b> a friendly minion, then summon a copy of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DAL_065 : Unsleeping Soul")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Unsleeping Soul"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasDeathrattle(), false);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_413] EVIL Conscripter - COST:2 [ATK:2/HP:2]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a <b>Lackey</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DAL_413 : EVIL Conscripter")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Conscripter"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsLackey(), true);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_721] Catrina Muerte - COST:8 [ATK:6/HP:8]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn, summon a friendly minion
//       that died this game.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - DAL_721 : Catrina Muerte")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Catrina Muerte"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    bool check = (curField[1]->card->name == "Wolfrider") ||
                 (curField[1]->card->name == "Wisp");
    CHECK_EQ(check, true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 3);
    const bool check1 = (curField[1]->card->name == "Wolfrider") ||
                        (curField[1]->card->name == "Wisp");
    const bool check2 = (curField[2]->card->name == "Wolfrider") ||
                        (curField[2]->card->name == "Wisp");
    check = check1 && check2;
    CHECK_EQ(check, true);
}

// ----------------------------------------- SPELL - PRIEST
// [DAL_723] Forbidden Words - COST:0
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Spend all your Mana. Destroy a minion with that
//       much Attack or less.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DAL_723 : Forbidden Words")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Forbidden Words"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opPlayer->GetRemainingMana(), 8);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetRemainingMana(), 0);
}

// ----------------------------------------- SPELL - PRIEST
// [DAL_724] Mass Resurrection - COST:9
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Summon 3 friendly minions that died this game.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DAL_724 : Mass Resurrection")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mass Resurrection"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 3);
    const bool check1 = (curField[0]->card->name == "Wolfrider") ||
                        (curField[0]->card->name == "Wisp") ||
                        (curField[0]->card->name == "Bloodfen Raptor");
    const bool check2 = (curField[1]->card->name == "Wolfrider") ||
                        (curField[1]->card->name == "Wisp") ||
                        (curField[1]->card->name == "Bloodfen Raptor");
    const bool check3 = (curField[2]->card->name == "Wolfrider") ||
                        (curField[2]->card->name == "Wisp") ||
                        (curField[2]->card->name == "Bloodfen Raptor");
    const bool check = check1 && check2 && check3;
    CHECK_EQ(check, true);
}

// ---------------------------------------- MINION - PRIEST
// [DAL_729] Madame Lazul - COST:3 [ATK:3/HP:2]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a
//       copy of a card in your opponent's hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - DAL_729 : Madame Lazul")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Madame Lazul"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    const bool check1 = (cards[0]->name == "The Coin") ||
                        (cards[0]->name == "Wolfrider") ||
                        (cards[0]->name == "Wisp");
    const bool check2 = (cards[1]->name == "The Coin") ||
                        (cards[1]->name == "Wolfrider") ||
                        (cards[1]->name == "Wisp");
    const bool check3 = (cards[2]->name == "The Coin") ||
                        (cards[2]->name == "Wolfrider") ||
                        (cards[2]->name == "Wisp");
    const bool check = check1 && check2 && check3;
    CHECK_EQ(check, true);
}

// ------------------------------------------ SPELL - ROGUE
// [DAL_010] Togwaggle's Scheme - COST:1
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Choose a minion. Shuffle @ (copy, copies) of it into your deck.
//       <i>(Upgrades each turn!)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_1 = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DAL_010 : Togwaggle's Scheme")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Togwaggle's Scheme"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curDeck.GetCount(), 2);
}

// ------------------------------------------ SPELL - ROGUE
// [DAL_366] Unidentified Contract - COST:6
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy a minion. Gains a bonus effect in your hand.
// --------------------------------------------------------
// Entourage: DAL_366t1, DAL_366t2, DAL_366t3, DAL_366t4
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DAL_366 : Unidentified Contract")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Unidentified Contract"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 2);

    if (card4->card->id == "DAL_366t1")
    {
        CHECK_EQ(opField.GetCount(), 1);
        CHECK_EQ(opField[0]->card->name, "Patient Assassin");
    }
    else if (card4->card->id == "DAL_366t2")
    {
        CHECK_EQ(opHand.GetCount(), 2);
        CHECK_EQ(opHand[1]->card->name, "Wolfrider");
    }
    else if (card4->card->id == "DAL_366t3")
    {
        CHECK_EQ(opHand.GetCount(), 3);
        CHECK_EQ(opHand[1]->card->name, "The Coin");
        CHECK_EQ(opHand[2]->card->name, "The Coin");
    }
    else
    {
        CHECK_EQ(curField[0]->GetHealth(), 1);
        CHECK_EQ(curField[1]->GetHealth(), 1);
    }
}

// ----------------------------------------- MINION - ROGUE
// [DAL_415] EVIL Miscreant - COST:3 [ATK:1/HP:5]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Add two random <b>Lackeys</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DAL_415 : EVIL Miscreant")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Miscreant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Miscreant"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->IsLackey(), true);
    CHECK_EQ(curHand[1]->card->IsLackey(), true);
}

// ----------------------------------------- MINION - ROGUE
// [DAL_416] Hench-Clan Burglar - COST:4 [ATK:4/HP:3]
// - Race: Pirate, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a spell from another class.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DAL_416 : Hench-Clan Burglar")
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
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Burglar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_NE(card->GetCardClass(), CardClass::ROGUE);
    }
}

// ----------------------------------------- MINION - ROGUE
// [DAL_417] Heistbaron Togwaggle - COST:6 [ATK:5/HP:5]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Lackey</b>,
//       choose a fantastic treasure.
// --------------------------------------------------------
// Entourage: LOOT_998h, LOOT_998j, LOOT_998l, LOOT_998k
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - MULTIPLY_BUFF_VALUE = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DAL_417 : Heistbaron Togwaggle")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wolfrider");
        config.player2Deck[i] = Cards::FindCardByName("Fireball");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_739"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heistbaron Togwaggle"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice == nullptr);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    curPlayer->SetUsedMana(0);

    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heistbaron Togwaggle"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heistbaron Togwaggle"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heistbaron Togwaggle"));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heistbaron Togwaggle"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twisting Nether"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 72);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 77);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 82);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK(curPlayer->choice != nullptr);

    Generic::ChoicePick(curPlayer, 87);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card7));
    CHECK_EQ(curField.GetCount(), 0);

    curPlayer->SetUsedMana(0);

    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[4]->card->name, "Tolin's Goblet");
    CHECK_EQ(curHand[5]->card->name, "Zarog's Crown");
    CHECK_EQ(curHand[6]->card->name, "Wondrous Wand");
    CHECK_EQ(curHand[7]->card->name, "Golden Kobold");

    // Wondrous Wand (LOOT_998l)
    game.Process(curPlayer, PlayCardTask::Spell(curHand[6]));
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(curHand[7]->card->name, "Wolfrider");
    CHECK_EQ(curHand[7]->GetCost(), 0);
    CHECK_EQ(curHand[8]->card->name, "Wolfrider");
    CHECK_EQ(curHand[8]->GetCost(), 0);
    CHECK_EQ(curHand[9]->card->name, "Wolfrider");
    CHECK_EQ(curHand[9]->GetCost(), 0);

    // Zarog's Crown (LOOT_998j)
    game.Process(curPlayer, PlayCardTask::Spell(curHand[5]));
    CHECK(curPlayer->choice != nullptr);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRarity(), Rarity::LEGENDARY);
    }

    Generic::ChoicePick(curPlayer, 88);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curField[0]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curField[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curField[1]->card->GetRarity(), Rarity::LEGENDARY);

    curPlayer->SetUsedMana(0);

    // Tolin's Goblet (LOOT_998h)
    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(curHand[8]->card->name, "Wolfrider");
    CHECK_EQ(curHand[8]->GetCost(), 3);
    CHECK_EQ(curHand[9]->card->name, "Wolfrider");
    CHECK_EQ(curHand[9]->GetCost(), 3);

    // Golden Kobold (LOOT_998k)
    game.Process(curPlayer, PlayCardTask::Minion(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 9);
    for (int i = 0; i < 9; ++i)
    {
        CHECK_EQ(curHand[i]->card->GetCardType(), CardType::MINION);
        CHECK_EQ(curHand[i]->card->GetRarity(), Rarity::LEGENDARY);
    }
}

// ----------------------------------------- MINION - ROGUE
// [DAL_714] Underbelly Fence - COST:2 [ATK:2/HP:3]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a card from
//       another class, gain +1/+1 and <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DAL_714 : Underbelly Fence")
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
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Underbelly Fence"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Underbelly Fence"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasRush(), false);
}

// ------------------------------------------ SPELL - ROGUE
// [DAL_716] Vendetta - COST:4
// - Faction: Neutral, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 4 damage to a minion. Costs (0) if you're
//       holding a card from another class.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DAL_716 : Vendetta")
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
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vendetta"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card1->GetCost(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(card1->GetCost(), 4);
}

// ----------------------------------------- MINION - ROGUE
// [DAL_719] Tak Nozwhisker - COST:7 [ATK:6/HP:6]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you shuffle a card into your deck,
//       add a copy to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - DAL_719 : Tak Nozwhisker")
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
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tak Nozwhisker"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Togwaggle's Scheme"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Tak Nozwhisker");
    CHECK_EQ(curDeck[0]->card->name, "Tak Nozwhisker");
}

// ----------------------------------------- WEAPON - ROGUE
// [DAL_720] Waggle Pick - COST:4 [ATK:4/HP:0]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Return a random friendly
//       minion to your hand. It costs (2) less.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Weapon] - DAL_720 : Waggle Pick")
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
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Waggle Pick"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 4);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(card2->GetCost(), 1);
}

// ------------------------------------------ SPELL - ROGUE
// [DAL_728] Daring Escape - COST:1
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Return all friendly minions to your hand.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - DAL_728 : Daring Escape")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Daring Escape"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opHand.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opHand.GetCount(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [DAL_009] Hagatha's Scheme - COST:5
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Deal @ damage to all minions.
//       <i>(Upgrades each turn!)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_1 = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DAL_009 : Hagatha's Scheme")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hagatha's Scheme"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 10);
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_047] Walking Fountain - COST:8 [ATK:4/HP:8]
// - Race: Elemental, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>, <b>Rush</b>, <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// - LIFESTEAL = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_047 : Walking Fountain")
{
    // Do nothing
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_049] Underbelly Angler - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: After you play a Murloc, add a random Murloc to your hand.
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_049 : Underbelly Angler")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Underbelly Angler"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[1]->card->GetRace(), Race::MURLOC);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 1);
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_052] Muckmorpher - COST:5 [ATK:4/HP:4]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform into a 4/4 copy of
//       a different minion in your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_052 : Muckmorpher")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Muckmorpher"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->name, "Malygos");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->GetSpellPower(), 5);
}

// ----------------------------------------- SPELL - SHAMAN
// [DAL_071] Mutate - COST:0
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Transform a friendly minion into a random one
//       that costs (1) more.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DAL_071 : Mutate")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mutate"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mutate"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[0]->GetCost(), 4);

    if (curField[0]->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS) == 0)
    {
        game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
        CHECK_EQ(curField[0]->GetCost(), 5);
    }
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_431] Swampqueen Hagatha - COST:7 [ATK:5/HP:5]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a 5/5 Horror to your hand.
//       Teach it two Shaman spells.
// --------------------------------------------------------
// Entourage: DAL_431t
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_431 : Swampqueen Hagatha")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Swampqueen Hagatha"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice != nullptr);

    TestUtils::ChooseNthChoice(game, 1);
    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Drustvar Horror");

    const int dbfID1 = curHand[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1);
    const int dbfID2 = curHand[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2);
    CHECK(dbfID1 > 0);
    CHECK(dbfID2 > 0);

    auto spell1 = Cards::FindCardByDbfID(dbfID1);
    auto spell2 = Cards::FindCardByDbfID(dbfID2);
    bool isSpell1TargetingCard = false;
    bool isSpell2TargetingCard = false;

    for (auto& playReq : spell1->playRequirements)
    {
        if (playReq.first == PlayReq::REQ_TARGET_TO_PLAY ||
            playReq.first == PlayReq::REQ_TARGET_IF_AVAILABLE)
        {
            isSpell1TargetingCard = true;
            break;
        }
    }

    for (auto& playReq : spell2->playRequirements)
    {
        if (playReq.first == PlayReq::REQ_TARGET_TO_PLAY ||
            playReq.first == PlayReq::REQ_TARGET_IF_AVAILABLE)
        {
            isSpell2TargetingCard = true;
            break;
        }
    }

    const bool check = isSpell1TargetingCard && isSpell2TargetingCard;
    CHECK_EQ(check, false);
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_431t] Drustvar Horror (*) - COST:5 [ATK:5/HP:5]
// - Set: Dalaran
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Cast {0} and {1}.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_431t : Drustvar Horror")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_431t"));
    card1->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1, 505);
    card1->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2, 818);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->GetCost(), 6);
}

// ----------------------------------------- SPELL - SHAMAN
// [DAL_432] Witch's Brew - COST:2
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Restore 4 Health. Repeatable this turn.
// --------------------------------------------------------
// GameTag:
// - NON_KEYWORD_ECHO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_432 : Witch's Brew")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(15);
    opPlayer->GetHero()->SetDamage(15);

    auto& curHand = *(curPlayer->GetHandZone());
    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Witch's Brew"));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curHero));
    CHECK_EQ(curHero->GetHealth(), 19);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Witch's Brew");
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::GHOSTLY), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[4], opHero));
    CHECK_EQ(opHero->GetHealth(), 19);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Witch's Brew");
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::GHOSTLY), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 4);
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_433] Sludge Slurper - COST:1 [ATK:2/HP:1]
// - Race: Murloc, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_433 : Sludge Slurper")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sludge Slurper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsLackey(), true);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
}

// ----------------------------------------- SPELL - SHAMAN
// [DAL_710] Soul of the Murloc - COST:2
// - Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions "<b>Deathrattle:</b> Summon a 1/1 Murloc."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - DAL_710 : Soul of the Murloc")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soul of the Murloc"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(curField[1]->HasDeathrattle(), false);
    CHECK_EQ(curField[2]->HasDeathrattle(), false);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);
    CHECK_EQ(curField[1]->HasDeathrattle(), true);
    CHECK_EQ(curField[2]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Murloc Scout");
    CHECK_EQ(curField[1]->card->name, "Murloc Scout");
    CHECK_EQ(curField[2]->card->name, "Chillwind Yeti");
}

// ---------------------------------------- MINION - SHAMAN
// [DAL_726] Scargil - COST:4 [ATK:4/HP:4]
// - Race: Murloc, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Your Murlocs cost (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - DAL_726 : Scargil")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scargil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Warleader"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bluegill Warrior"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card1));
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 3);
}

// ---------------------------------------- SPELL - WARLOCK
// [DAL_007] Rafaam's Scheme - COST:3
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Summon @ 1/1 (Imp, Imps). <i>(Upgrades each turn!)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_1 = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DAL_007 : Rafaam's Scheme")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rafaam's Scheme"));

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Imp");
    CHECK_EQ(curField[1]->card->name, "Imp");
}

// ---------------------------------------- SPELL - WARLOCK
// [DAL_173] Darkest Hour - COST:6
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy all friendly minions.
//       For each one, summon a random minion from your deck.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DAL_173 : Darkest Hour")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wolfrider");
        config.player1Deck[i + 1] = Cards::FindCardByName("Rafaam's Scheme");
        config.player1Deck[i + 2] = Cards::FindCardByName("Siegebreaker");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darkest Hour"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);

    const bool check1 = (curField[0]->card->name == "Wolfrider" ||
                         curField[0]->card->name == "Siegebreaker");
    const bool check2 = (curField[1]->card->name == "Wolfrider" ||
                         curField[1]->card->name == "Siegebreaker");
    const bool check3 = (curField[2]->card->name == "Wolfrider" ||
                         curField[2]->card->name == "Siegebreaker");
    const bool check = check1 && check2 && check3;
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - WARLOCK
// [DAL_185] Aranasi Broodmother - COST:6 [ATK:4/HP:6]
// - Race: Demon, Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> When you draw this,
//       restore 4 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TOPDECK = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_185 : Aranasi Broodmother")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Aranasi Broodmother");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curPlayer->GetHero()->SetDamage(15);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
}

// --------------------------------------- MINION - WARLOCK
// [DAL_422] Arch-Villain Rafaam - COST:7 [ATK:7/HP:8]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> Replace your hand
//       and deck with <b>Legendary</b> minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_422 : Arch-Villain Rafaam")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arch-Villain Rafaam"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    for (auto& handCard : curHand.GetAll())
    {
        CHECK_EQ(handCard->card->GetCardType(), CardType::MINION);
        CHECK_EQ(handCard->card->GetRarity(), Rarity::LEGENDARY);
    }
    for (auto& deckCard : curDeck.GetAll())
    {
        CHECK_EQ(deckCard->card->GetCardType(), CardType::MINION);
        CHECK_EQ(deckCard->card->GetRarity(), Rarity::LEGENDARY);
    }
}

// --------------------------------------- MINION - WARLOCK
// [DAL_561] Jumbo Imp - COST:10 [ATK:8/HP:8]
// - Race: Demon, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less whenever a friendly Demon dies
//       while this is in your hand.
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_561 : Jumbo Imp")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jumbo Imp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Shadowhoof Slayer"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card1->GetCost(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(card1->GetCost(), 9);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, HeroPowerTask(card5));
    CHECK_EQ(card1->GetCost(), 9);
}

// --------------------------------------- MINION - WARLOCK
// [DAL_563] Eager Underling - COST:4 [ATK:2/HP:2]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give two random friendly minions +2/+2.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_563 : Eager Underling")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eager Underling"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    const bool check1 =
        curField[0]->GetAttack() == 5 && curField[0]->GetHealth() == 4 &&
        curField[1]->GetAttack() == 3 && curField[1]->GetHealth() == 3 &&
        curField[2]->GetAttack() == 3 && curField[2]->GetHealth() == 1;
    const bool check2 =
        curField[0]->GetAttack() == 5 && curField[0]->GetHealth() == 4 &&
        curField[1]->GetAttack() == 1 && curField[1]->GetHealth() == 1 &&
        curField[2]->GetAttack() == 5 && curField[2]->GetHealth() == 3;
    const bool check3 =
        curField[0]->GetAttack() == 3 && curField[0]->GetHealth() == 2 &&
        curField[1]->GetAttack() == 3 && curField[1]->GetHealth() == 3 &&
        curField[2]->GetAttack() == 5 && curField[2]->GetHealth() == 3;
    const bool check = check1 || check2 || check3;
    CHECK_EQ(check, true);
}

// ---------------------------------------- SPELL - WARLOCK
// [DAL_602] Plot Twist - COST:2
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Shuffle your hand into your deck. Draw that many cards.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DAL_602 : Plot Twist")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Aranasi Broodmother");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(25);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plot Twist"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 21);
}

// ---------------------------------------- SPELL - WARLOCK
// [DAL_605] Impferno - COST:3
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Give your Demons +1 Attack.
//       Deal 1 damage to all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - DAL_605 : Impferno")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Impferno"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Voidwalker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 2);
    CHECK_EQ(opField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [DAL_606] EVIL Genius - COST:2 [ATK:2/HP:2]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a friendly minion
//       to add 2 random <b>Lackeys</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_606 : EVIL Genius")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Genius"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Genius"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->IsLackey(), true);
    CHECK_EQ(curHand[5]->card->IsLackey(), true);
}

// --------------------------------------- MINION - WARLOCK
// [DAL_607] Fel Lord Betrug - COST:8 [ATK:5/HP:7]
// - Race: Demon, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you draw a minion, summon a copy
//       with <b>Rush</b> that dies at end of turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - DAL_607 : Fel Lord Betrug")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fel Lord Betrug"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Wisp");
    CHECK_EQ(curField[1]->HasRush(), true);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[4]));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Wisp");
    CHECK_EQ(curField[2]->HasRush(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Fel Lord Betrug");
    CHECK_EQ(curField[1]->card->name, "Wisp");
    CHECK_EQ(curField[1]->HasRush(), false);
}

// ---------------------------------------- SPELL - WARRIOR
// [DAL_008] Dr. Boom's Scheme - COST:4
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Gain @ Armor. <i>(Upgrades each turn!)</i>
// --------------------------------------------------------
// GameTag:
// - TAG_SCRIPT_DATA_NUM_1 = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DAL_008 : Dr. Boom's Scheme")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dr. Boom's Scheme"));

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ---------------------------------------- SPELL - WARRIOR
// [DAL_059] Dimensional Ripper - COST:10
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Summon 2 copies of a minion in your deck.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DAL_059 : Dimensional Ripper")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dimensional Ripper"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wisp");
    CHECK_EQ(curField[1]->card->name, "Wisp");
    CHECK_EQ(curDeck.GetCount(), 26);
}

// --------------------------------------- MINION - WARRIOR
// [DAL_060] Clockwork Goblin - COST:3 [ATK:3/HP:3]
// - Race: Mechanical, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle a Bomb into your opponent's deck.
//       When drawn, it explodes for 5 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DAL_060 : Clockwork Goblin")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Clockwork Goblin"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opDeck.GetCount(), 1);
    CHECK_EQ(opDeck[0]->card->name, "Bomb");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 10);
}

// ---------------------------------------- SPELL - WARRIOR
// [DAL_062] Sweeping Strikes - COST:2
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion "Also damages minions next to whomever this attacks."
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DAL_062 : Sweeping Strikes")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Reservoir"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sweeping Strikes"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[2]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card5));

    game.Process(opPlayer, AttackTask(card5, card2));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// --------------------------------------- WEAPON - WARRIOR
// [DAL_063] Wrenchcalibur - COST:4 [ATK:3/HP:0]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: After your hero attacks, shuffle a Bomb
//       into your opponent's deck.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - DAL_063 : Wrenchcalibur")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wrenchcalibur"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);
    CHECK_EQ(opDeck.GetCount(), 1);
    CHECK_EQ(opDeck[0]->card->name, "Bomb");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 7);
}

// --------------------------------------- MINION - WARRIOR
// [DAL_064] Blastmaster Boom - COST:7 [ATK:7/HP:7]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Boom Bots
//       for each Bomb in your opponent's deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DAL_064 : Blastmaster Boom")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blastmaster Boom"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Clockwork Goblin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Clockwork Goblin"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opDeck.GetCount(), 2);
    CHECK_EQ(opDeck[0]->card->name, "Bomb");
    CHECK_EQ(opDeck[1]->card->name, "Bomb");

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[2]->card->name, "Boom Bot");
    CHECK_EQ(curField[3]->card->name, "Boom Bot");
    CHECK_EQ(curField[4]->card->name, "Blastmaster Boom");
    CHECK_EQ(curField[5]->card->name, "Boom Bot");
    CHECK_EQ(curField[6]->card->name, "Boom Bot");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opDeck.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 5);

    game.Process(opPlayer, HeroPowerTask(curField[2]));
    const int opHeroHealth = opPlayer->GetHero()->GetHealth();
    const bool check = (opHeroHealth == 1) || (opHeroHealth == 2) ||
                       (opHeroHealth == 3) || (opHeroHealth == 4);
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - WARRIOR
// [DAL_070] The Boom Reaver - COST:10 [ATK:7/HP:9]
// - Race: Mechanical, Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a copy of a minion in your deck.
//       Give it <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DAL_070 : The Boom Reaver")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player2Deck[i] = Cards::FindCardByName("Wolfrider");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Boom Reaver"));

    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "The Boom Reaver");
    CHECK_EQ(curField[1]->card->name, "Malygos");
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curDeck.GetCount(), 26);
}

// --------------------------------------- MINION - WARRIOR
// [DAL_759] Vicious Scraphound - COST:2 [ATK:2/HP:2]
// - Race: Mechanical, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion deals damage, gain that much Armor.
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - DAL_759 : Vicious Scraphound")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vicious Scraphound"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);
}

// ---------------------------------------- SPELL - WARRIOR
// [DAL_769] Improve Morale - COST:1
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage to a minion.
//       If it survives, add a <b>Lackey</b> to your hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DAL_769 : Improve Morale")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Improve Morale"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Improve Morale"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opHand.GetCount(), 8);
    CHECK_EQ(opHand[7]->card->IsLackey(), true);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opHand.GetCount(), 7);
}

// --------------------------------------- MINION - WARRIOR
// [DAL_770] Omega Devastator - COST:4 [ATK:4/HP:5]
// - Race: Mechanical, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
//       deal 10 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - DAL_770 : Omega Devastator")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(8);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Omega Devastator"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Omega Devastator"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_058] Hecklebot - COST:4 [ATK:3/HP:8]
// - Race: Mechanical, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Battlecry:</b> Your opponent
//       summons a minion from their deck.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_058 : Hecklebot")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wolfrider");
        config.player2Deck[i] = Cards::FindCardByName("Onyxia");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hecklebot"));

    CHECK_EQ(opDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Onyxia");
    CHECK_EQ(opDeck.GetCount(), 25);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_077] Toxfin - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly Murloc <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_RACE = 14
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_077 : Toxfin")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(3);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Toxfin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->HasPoisonous(), true);
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
TEST_CASE("[Neutral : Minion] - DAL_078 : Travelling Healer")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

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
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(opPlayer, PlayCardTask::Weapon(card2));
    game.Process(opPlayer, AttackTask(opHero, curField[0]));

    CHECK_EQ(curField[0]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_081] Spellward Jeweler - COST:3 [ATK:3/HP:4]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your hero can't be targeted by
//       spells or Hero Powers until your next turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_081 : Spellward Jeweler")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto curHero = curPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Spellward Jeweler"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS), 1);
    CHECK_EQ(curHero->GetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curHero));
    CHECK_EQ(curHero->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHero->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS), 0);
    CHECK_EQ(curHero->GetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curHero));
    CHECK_EQ(curHero->GetHealth(), 29);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_085] Dalaran Crusader - COST:5 [ATK:5/HP:4]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_085 : Dalaran Crusader")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_086] Sunreaver Spy - COST:2 [ATK:2/HP:3]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_086 : Sunreaver Spy")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sunreaver Spy"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sunreaver Spy"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_087] Hench-Clan Hag - COST:4 [ATK:3/HP:3]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Amalgams
//       with all minion types.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_087 : Hench-Clan Hag")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hench-Clan Hag"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Amalgam");
    CHECK_EQ(curField[1]->card->name, "Hench-Clan Hag");
    CHECK_EQ(curField[2]->card->name, "Amalgam");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_088] Safeguard - COST:6 [ATK:4/HP:5]
// - Race: Mechanical, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a 0/5
//       Vault Safe with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_088 : Safeguard")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Safeguard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Safeguard");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Vault Safe");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_089] Spellbook Binder - COST:2 [ATK:3/HP:2]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have <b>Spell Damage</b>,
//       draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_089 : Spellbook Binder")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbook Binder"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbook Binder"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 0);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 1);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_090] Hench-Clan Sneak - COST:3 [ATK:3/HP:3]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_090 : Hench-Clan Sneak")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_092] Arcane Servant - COST:2 [ATK:2/HP:3]
// - Race: Elemental, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_092 : Arcane Servant")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_095] Violet Spellsword - COST:4 [ATK:1/HP:6]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1 Attack
//       for each spell in your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_095 : Violet Spellsword")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Violet Spellsword"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Violet Spellsword"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_096] Violet Warden - COST:6 [ATK:4/HP:7]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_096 : Violet Warden")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_400] EVIL Cable Rat - COST:2 [ATK:1/HP:1]
// - Race: Beast, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - MARK_OF_EVIL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_400 : EVIL Cable Rat")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("EVIL Cable Rat"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsLackey(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_434] Arcane Watcher - COST:3 [ATK:5/HP:6]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack unless you have <b>Spell Damage</b>.
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_434 : Arcane Watcher")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Watcher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_538] Unseen Saboteur - COST:6 [ATK:5/HP:6]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your opponent casts a random spell
//       from their hand <i>(targets chosen randomly)</i>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_538 : Unseen Saboteur")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Unseen Saboteur"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curPlayer->GetHero()->SetDamage(0);
    opPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 0);

    const bool check1 = curPlayer->GetHero()->GetHealth() == 24 &&
                        opField.GetCount() == 1 &&
                        opPlayer->GetHero()->GetHealth() == 30;
    const bool check2 = curPlayer->GetHero()->GetHealth() == 30 &&
                        opField.GetCount() == 0 &&
                        opPlayer->GetHero()->GetHealth() == 30;
    const bool check3 = curPlayer->GetHero()->GetHealth() == 30 &&
                        opField.GetCount() == 1 &&
                        opPlayer->GetHero()->GetHealth() == 24;
    const bool check = check1 || check2 || check3;
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_539] Sunreaver Warmage - COST:5 [ATK:4/HP:4]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a spell that
//       costs (5) or more, deal 4 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_DRAG_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_539 : Sunreaver Warmage")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sunreaver Warmage"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sunreaver Warmage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_544] Potion Vendor - COST:1 [ATK:1/HP:1]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 2 Health to all friendly characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_544 : Potion Vendor")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Potion Vendor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curField[0]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_546] Barista Lynchen - COST:5 [ATK:4/HP:5]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a copy of each of your other
//       <b>Battlecry</b> minions to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_546 : Barista Lynchen")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Barista Lynchen"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hench-Clan Sneak"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Potion Vendor"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Toxfin"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Potion Vendor");
    CHECK_EQ(curHand[1]->card->name, "Toxfin");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_548] Azerite Elemental - COST:5 [ATK:2/HP:7]
// - Race: Elemental, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: At the start of your turn, gain <b>Spell Damage +2</b>.
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_548 : Azerite Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Azerite Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_550] Underbelly Ooze - COST:7 [ATK:3/HP:5]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: After this minion survives damage, summon a copy of it.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_550 : Underbelly Ooze")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Underbelly Ooze"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Underbelly Ooze");
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->card->name, "Underbelly Ooze");
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_551] Proud Defender - COST:4 [ATK:2/HP:6]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Has +2 Attack while you have no other minions.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_551 : Proud Defender")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Proud Defender"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_553] Big Bad Archmage - COST:10 [ATK:6/HP:6]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: At the end of your turn, summon a random
//       6-Cost minion.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_553 : Big Bad Archmage")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Big Bad Archmage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetCost(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_554] Chef Nomi - COST:7 [ATK:6/HP:6]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck is empty,
//       summon six 6/6 Greasefire Elementals.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_554 : Big Bad Archmage")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Marked Shot");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chef Nomi"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chef Nomi"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Chef Nomi");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 7);
    CHECK_EQ(opField[0]->card->name, "Greasefire Elemental");
    CHECK_EQ(opField[1]->card->name, "Greasefire Elemental");
    CHECK_EQ(opField[2]->card->name, "Greasefire Elemental");
    CHECK_EQ(opField[3]->card->name, "Chef Nomi");
    CHECK_EQ(opField[4]->card->name, "Greasefire Elemental");
    CHECK_EQ(opField[5]->card->name, "Greasefire Elemental");
    CHECK_EQ(opField[6]->card->name, "Greasefire Elemental");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_558] Archmage Vargoth - COST:4 [ATK:2/HP:6]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn, cast a spell
//       you've cast this turn <i>(targets are random)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_558 : Archmage Vargoth")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Archmage Vargoth"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const bool check1 = (curHero->GetHealth() == 27) &&
                        (curField[0]->GetHealth() == 6) &&
                        (opHero->GetHealth() == 27);
    const bool check2 = (curHero->GetHealth() == 30) &&
                        (curField[0]->GetHealth() == 3) &&
                        (opHero->GetHealth() == 27);
    const bool check3 = (curHero->GetHealth() == 30) &&
                        (curField[0]->GetHealth() == 6) &&
                        (opHero->GetHealth() == 24);
    const bool check = check1 || check2 || check3;
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_560] Heroic Innkeeper - COST:8 [ATK:4/HP:4]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt.</b> <b>Battlecry:</b> Gain +2/+2
//       for each other friendly minion.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_560 : Heroic Innkeeper")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heroic Innkeeper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Heroic Innkeeper"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[3]->GetAttack(), 10);
    CHECK_EQ(curField[3]->GetHealth(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_565] Portal Overfiend - COST:6 [ATK:5/HP:6]
// - Race: Demon, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
//       When drawn, summon a 2/2 Demon with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_565 : Portal Overfiend")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Portal Overfiend"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Felhound");
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[2]->card->name, "Felhound");
    CHECK_EQ(curField[2]->HasRush(), true);
    CHECK_EQ(curField[3]->card->name, "Felhound");
    CHECK_EQ(curField[3]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_566] Eccentric Scribe - COST:6 [ATK:6/HP:4]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon four 1/1 Vengeful Scrolls.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_566 : Eccentric Scribe")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eccentric Scribe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Vengeful Scroll");
    CHECK_EQ(curField[1]->card->name, "Vengeful Scroll");
    CHECK_EQ(curField[2]->card->name, "Vengeful Scroll");
    CHECK_EQ(curField[3]->card->name, "Vengeful Scroll");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_582] Portal Keeper - COST:4 [ATK:5/HP:2]
// - Race: Demon, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
//       When drawn, summon a 2/2 Demon with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_582 : Portal Keeper")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Portal Keeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Felhound");
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[2]->card->name, "Felhound");
    CHECK_EQ(curField[2]->HasRush(), true);
    CHECK_EQ(curField[3]->card->name, "Felhound");
    CHECK_EQ(curField[3]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_592] Batterhead - COST:8 [ATK:3/HP:12]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b>. After this attacks and kills a minion,
//       it may attack again.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_592 : Batterhead")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Batterhead"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(card4->IsExhausted(), false);

    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(card4->IsExhausted(), false);

    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(card4->IsExhausted(), false);

    game.Process(opPlayer, AttackTask(card4, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(card4->IsExhausted(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_735] Dalaran Librarian - COST:2 [ATK:2/HP:3]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Silence</b> adjacent minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_735 : Dalaran Librarian")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dalaran Librarian"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[1]->GetSpellPower(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_736] Archivist Elysiana - COST:8 [ATK:7/HP:7]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> 5 cards.
//       Replace your deck with 2 copies of each.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_736 : Archivist Elysiana")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Archivist Elysiana"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    std::vector<int> chosenCards;
    chosenCards.reserve(5);
    for (int i = 0; i < 5; ++i)
    {
        const int dbfID = TestUtils::ChooseNthChoice(game, 1)->card->dbfID;
        chosenCards.emplace_back(dbfID);
    }
    std::sort(chosenCards.begin(), chosenCards.end());
    auto last = std::unique(chosenCards.begin(), chosenCards.end());
    chosenCards.erase(last, chosenCards.end());

    CHECK_EQ(curDeck.GetCount(), 10);

    std::vector<int> deckCards;
    for (auto& deckCard : curDeck.GetAll())
    {
        deckCards.emplace_back(deckCard->card->dbfID);
    }
    std::sort(deckCards.begin(), deckCards.end());
    last = std::unique(deckCards.begin(), deckCards.end());
    deckCards.erase(last, deckCards.end());

    CHECK_EQ(chosenCards, deckCards);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_742] Whirlwind Tempest - COST:8 [ATK:6/HP:6]
// - Race: Elemental, Faction: Neutral, Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: Your minions with <b>Windfury</b> have <b>Mega-Windfury</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - WINDFURY = 1
// - MEGA_WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_742 : Whirlwind Tempest")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Whirlwind Tempest"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Thrallmar Farseer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[0]->HasMegaWindfury(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->IsExhausted(), false);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->IsExhausted(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[0]->HasMegaWindfury(), true);
    CHECK_EQ(curField[0]->IsExhausted(), false);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->IsExhausted(), false);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->IsExhausted(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[0]->HasMegaWindfury(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_743] Hench-Clan Hogsteed - COST:2 [ATK:2/HP:1]
// - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Deathrattle:</b> Summon a 1/1 Murloc.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_743 : Hench-Clan Hogsteed")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hench-Clan Hogsteed"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Hench-Clan Squire");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_744] Faceless Rager - COST:3 [ATK:5/HP:1]
// - Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Copy a friendly minion's Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_744 : Faceless Rager")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faceless Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_747] Flight Master - COST:3 [ATK:3/HP:4]
// - Faction: Alliance, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/2 Gryphon for each player.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_747 : Flight Master")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flight Master"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Gryphon");
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Gryphon");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_748] Mana Reservoir - COST:2 [ATK:0/HP:6]
// - Race: Elemental, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_748 : Mana Reservoir")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_749] Recurring Villain - COST:5 [ATK:3/HP:6]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> If this minion has 4 or more Attack,
//       resummon it.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_749 : Recurring Villain")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Recurring Villain"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blessing of Might"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, curField[0]));
    CHECK_EQ(curField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_751] Mad Summoner - COST:6 [ATK:4/HP:4]
// - Race: Demon, Faction: Alliance, Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Fill each player's board with 1/1 Imps.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_751 : Mad Summoner")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mad Summoner"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->card->name, "Imp");
    CHECK_EQ(curField[1]->card->name, "Imp");
    CHECK_EQ(curField[2]->card->name, "Imp");
    CHECK_EQ(curField[3]->card->name, "Mad Summoner");
    CHECK_EQ(curField[4]->card->name, "Imp");
    CHECK_EQ(curField[5]->card->name, "Imp");
    CHECK_EQ(curField[6]->card->name, "Imp");
    CHECK_EQ(opField.GetCount(), 7);
    CHECK_EQ(opField[0]->card->name, "Imp");
    CHECK_EQ(opField[1]->card->name, "Imp");
    CHECK_EQ(opField[2]->card->name, "Imp");
    CHECK_EQ(opField[3]->card->name, "Imp");
    CHECK_EQ(opField[4]->card->name, "Imp");
    CHECK_EQ(opField[5]->card->name, "Imp");
    CHECK_EQ(opField[6]->card->name, "Imp");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_752] Jepetto Joybuzz - COST:8 [ATK:6/HP:6]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw 2 minions from your deck.
//       Set their Attack, Health, and Cost to 1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_752 : Jepetto Joybuzz")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 1] = Cards::FindCardByName("Never Surrender!");
        config.player1Deck[i + 2] = Cards::FindCardByName("Nozari");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jepetto Joybuzz"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);

    const bool check = (curHand[4]->card->name == "Malygos" ||
                        curHand[4]->card->name == "Nozari") &&
                       (curHand[5]->card->name == "Malygos" ||
                        curHand[5]->card->name == "Nozari");
    CHECK_EQ(check, true);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::ATK), 1);
    CHECK_EQ(curHand[4]->GetGameTag(GameTag::HEALTH), 1);
    CHECK_EQ(curHand[4]->GetCost(), 1);
    CHECK_EQ(curHand[5]->GetGameTag(GameTag::ATK), 1);
    CHECK_EQ(curHand[5]->GetGameTag(GameTag::HEALTH), 1);
    CHECK_EQ(curHand[5]->GetCost(), 1);
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
TEST_CASE("[Neutral : Minion] - DAL_760 : Burly Shovelfist")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_771] Soldier of Fortune - COST:4 [ATK:5/HP:6]
// - Race: Elemental, Set: Dalaran, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion attacks, give your opponent a Coin.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_771 : Soldier of Fortune")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soldier of Fortune"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opHand.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opHand.GetCount(), 2);
    CHECK_EQ(opHand[1]->card->name, "The Coin");
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_773] Magic Carpet - COST:3 [ATK:1/HP:6]
// - Set: Dalaran, Rarity: Epic
// --------------------------------------------------------
// Text: After you play a 1-Cost minion,
//       give it +1 Attack and <b>Rush</b>.
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_773 : Magic Carpet")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magic Carpet"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_774] Exotic Mountseller - COST:7 [ATK:5/HP:8]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, summon a random 3-Cost Beast.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_774 : Exotic Mountseller")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Exotic Mountseller"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetCost(), 3);
    CHECK_EQ(curField[1]->card->GetRace(), Race::BEAST);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->GetCost(), 3);
    CHECK_EQ(curField[2]->card->GetRace(), Race::BEAST);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_775] Tunnel Blaster - COST:7 [ATK:3/HP:7]
// - Set: Dalaran, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b> <b>Deathrattle:</b> Deal 3 damage
//       to all minions.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_775 : Tunnel Blaster")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tunnel Blaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironfur Grizzly"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 9);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - NEUTRAL
// [DAL_800] Zayle, Shadow Cloak - COST:2 [ATK:3/HP:2]
// - Set: Dalaran, Rarity: Legendary
// --------------------------------------------------------
// Text: You start the game with one of Zayle's EVIL Decks!
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DAL_800 : Zayle, Shadow Cloak")
{
    // Do nothing
}