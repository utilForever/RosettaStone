// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

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
// [SW_422] Sow the Soil - COST:1
// - Set: STORMWIND, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One</b> - Give your minions +1 Attack;
//       or Summon a 2/2 Treant.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_422 : Sow the Soil")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sow the Soil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sow the Soil"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Treant");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [SW_428] Lost in the Park - COST:1
// - Set: STORMWIND, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Questline:</b> Gain 4 Attack with your hero.
//       <b>Reward:</b> Gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_428 : Lost in the Park")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lost in the Park"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 1));
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(curSecret->quest->card->name, "Defend the Squirrels");
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3, 1));
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 9);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card5));
    CHECK(curSecret->quest != nullptr);
    CHECK_EQ(curSecret->quest->card->name, "Feral Friendsy");
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 0);
    CHECK_EQ(curSecret->quest->GetQuestProgressTotal(), 6);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 11);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);
    CHECK_EQ(curHand.GetCount(), 7);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card4, 1));
    CHECK_EQ(curSecret->quest->GetQuestProgress(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 15);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);

    game.Process(curPlayer, PlayCardTask::Spell(card6));
    CHECK(curSecret->quest == nullptr);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 17);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 11);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Guff the Tough");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[5]));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 25);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 19);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 19);
}

// ------------------------------------------ SPELL - DRUID
// [SW_429] Best in Shell - COST:6
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       Summon two 2/7 Turtles with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - TRADEABLE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_429 : Best in Shell")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Best in Shell"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Goldshell Turtle");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Goldshell Turtle");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ----------------------------------------- MINION - DRUID
// [SW_431] Park Panther - COST:4 [ATK:4/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>. Whenever this attacks,
//       give your hero +3 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SW_431 : Park Panther")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Park Panther"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [SW_432] Kodo Mount - COST:4
// - Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion +4/+2 and <b>Rush</b>.
//       When it dies, summon a Kodo.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - SW_432 : Kodo Mount")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kodo Mount"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Guff's Kodo");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasRush(), true);
}

// ----------------------------------------- MINION - DRUID
// [SW_436] Wickerclaw - COST:2 [ATK:1/HP:4]
// - Race: Beast, Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: After your hero gains Attack,
//       this minion gains +2 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - SW_436 : Wickerclaw")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wickerclaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 5);
}

// ------------------------------------------ SPELL - DRUID
// [SW_437] Composting - COST:2
// - Set: STORMWIND, Rarity: Epic
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your minions "<b>Deathrattle:</b> Draw a card."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - SW_437 : Composting")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Composting"));
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

    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curField.GetCount(), 1);
}

// ----------------------------------------- MINION - DRUID
// [SW_439] Vibrant Squirrel - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: STORMWIND, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Shuffle 4 Acorns into your deck.
//       When drawn, summon a 2/1 Squirrel.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_439 : Vibrant Squirrel")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vibrant Squirrel"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curDeck.GetCount(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Satisfied Squirrel");
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [SW_055] Impatient Shopkeep - COST:3 [ATK:3/HP:3]
// - Set: STORMWIND, Rarity: Common
// --------------------------------------------------------
// Text: <b>Tradeable</b>
//       <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - TRADEABLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - SW_055 : Impatient Shopkeep")
{
    // Do nothing
}