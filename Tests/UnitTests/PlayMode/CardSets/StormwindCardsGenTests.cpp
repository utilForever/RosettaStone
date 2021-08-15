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

    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lost in the Park"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));

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