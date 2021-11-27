// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
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