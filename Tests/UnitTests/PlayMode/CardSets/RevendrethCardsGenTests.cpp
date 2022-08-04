// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// --------------------------------------- MINION - NEUTRAL
// [REV_956] Priest of the Deceased - COST:2 [ATK:2/HP:3]
// - Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Infuse (3):</b> Gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_956 : Priest of the Deceased")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Priest of the Deceased"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(card1->HasInfuse(), true);
    CHECK_EQ(dynamic_cast<Minion*>(card1)->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card1)->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [REV_957] Murlocula - COST:4 [ATK:3/HP:4]
// - Race: Murloc, Set: REVENDRETH, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       <b>Infuse (4):</b> This costs (0).
// --------------------------------------------------------
// GameTag:
// - INFUSE = 1
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - REV_957 : Murlocula")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murlocula"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(card1->HasInfuse(), true);
    CHECK_EQ(card1->GetCost(), 4);
    CHECK_EQ(card1->HasLifesteal(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand[0]->IsInfused(), true);
    CHECK_EQ(curHand[0]->GetCost(), 0);
    CHECK_EQ(curHand[0]->HasLifesteal(), true);
}