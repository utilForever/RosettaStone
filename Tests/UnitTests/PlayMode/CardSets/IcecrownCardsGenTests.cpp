// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

// ---------------------------------------- MINION - HUNTER
// [ICC_419] Bearshark - COST:3 [ATK:4/HP:3]
// - Race: Beast, Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - ICC_419 : Bearshark")
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - ICC_038 : Righteous Protector")
{
    // Do nothing
}

// ----------------------------------------- MINION - ROGUE
// [ICC_809] Plague Scientist - COST:3 [ATK:2/HP:3]
// - Set: Icecrown, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Give a friendly minion <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - ICC_809 : Plague Scientist")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->HasPoisonous(), true);
    CHECK_EQ(curField[1]->HasPoisonous(), false);
}