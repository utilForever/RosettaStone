// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ----------------------------------------- SPELL - HUNTER
// [DRG_255] Toxic Reinforcements - COST:1
// - Set: Dragons, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Sidequest:</b> Use your Hero Power three times.
//       <b>Reward:</b> Summon three 1/1 Leper Gnomes.
// --------------------------------------------------------
// GameTag:
// - QUEST_PROGRESS_TOTAL = 3
// - QUEST_REWARD_DATABASE_ID = 41127
// - SIDEQUEST = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - DRG_255 : Toxic Reinforcements")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Toxic Reinforcements"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(quest->GetQuestProgress(), 0);
    CHECK_EQ(quest->GetQuestProgressTotal(), 3);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(quest->GetQuestProgress(), 3);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->id, "DRG_255t2");
    CHECK_EQ(curField[1]->card->id, "DRG_255t2");
    CHECK_EQ(curField[2]->card->id, "DRG_255t2");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opPlayer->GetHero()->SetDamage(0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, AttackTask(card2, curField[0]));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_065] Hippogryph - COST:4 [ATK:2/HP:6]
// - Race: Beast, Set: Dragons, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_065 : Hippogryph")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [DRG_239] Blazing Battlemage - COST:1 [ATK:2/HP:2]
// - Set: Dragons, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - DRG_239 : Blazing Battlemage")
{
    // Do nothing
}