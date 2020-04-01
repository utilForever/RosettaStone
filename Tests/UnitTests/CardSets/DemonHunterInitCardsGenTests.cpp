// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_173] Command the Illidari - COST:5
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Summon six 1/1 Illidari with <b>Rush</b>.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_173 : Command the Illidari")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DEMONHUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Command the Illidari"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 6);
    CHECK_EQ(opField[0]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->IsRush(), true);
    CHECK_EQ(opField[1]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->IsRush(), true);
    CHECK_EQ(opField[2]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[2]->GetAttack(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 1);
    CHECK_EQ(opField[2]->IsRush(), true);
    CHECK_EQ(opField[3]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[3]->GetAttack(), 1);
    CHECK_EQ(opField[3]->GetHealth(), 1);
    CHECK_EQ(opField[3]->IsRush(), true);
    CHECK_EQ(opField[4]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[4]->GetAttack(), 1);
    CHECK_EQ(opField[4]->GetHealth(), 1);
    CHECK_EQ(opField[4]->IsRush(), true);
    CHECK_EQ(opField[5]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[5]->GetAttack(), 1);
    CHECK_EQ(opField[5]->GetHealth(), 1);
    CHECK_EQ(opField[5]->IsRush(), true);

    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_175] Twin Slice - COST:0
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +1 Attack this turn.
//       Add 'Second Slice' to your hand.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_175 : Twin Slice")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twin Slice"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Second Slice");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}