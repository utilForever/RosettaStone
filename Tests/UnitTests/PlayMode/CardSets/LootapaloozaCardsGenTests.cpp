// Copyright (c) 2017-2021 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ---------------------------------------- WEAPON - HUNTER
// [LOOT_222] Candleshot - COST:1 [ATK:1/HP:0]
// - Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Immune</b> while attacking.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - LOOT_222 : Candleshot")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Candleshot"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 1);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_124] Lone Champion - COST:3 [ATK:2/HP:4]
// - Set: Lootapalooza, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control no other minions,
//       gain <b>Taunt</b> and <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_124 : Lone Champion")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_125] Stoneskin Basilisk - COST:3 [ATK:1/HP:1]
// - Race: Beast, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
//       <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_125 : Stoneskin Basilisk")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [LOOT_137] Sleepy Dragon - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: Lootapalooza, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - LOOT_137 : Sleepy Dragon")
{
    // Do nothing
}