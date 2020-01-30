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

// ---------------------------------------- SPELL - PALADIN
// [ULD_431] Making Mummies - COST:1
// - Set: Uldum, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Quest:</b> Play 5 <b>Reborn</b> minions.
//       <b>Reward:</b> Emperor Wraps.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - QUEST = 1
// - QUEST_PROGRESS_TOTAL = 5
// - 676 = 1
// - 839 = 1
// - QUEST_REWARD_DATABASE_ID = 53908
// --------------------------------------------------------
// RefTag:
// - REBORN = 1
// --------------------------------------------------------
TEST(PaladinUldumTest, ULD_431_MakingMummies)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto curHero = curPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());
    const auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Making Mummies"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murmy"));

    auto quest = dynamic_cast<Spell*>(card1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_TRUE(curSecret->quest != nullptr);
    EXPECT_EQ(quest->GetQuestProgress(), 0);
    EXPECT_EQ(quest->GetQuestProgressTotal(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(quest->GetQuestProgress(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(quest->GetQuestProgress(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    EXPECT_EQ(quest->GetQuestProgress(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    EXPECT_EQ(quest->GetQuestProgress(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    EXPECT_TRUE(curSecret->quest == nullptr);
    EXPECT_EQ(quest->GetQuestProgress(), 5);
    EXPECT_EQ(curHero->heroPower->card->id, "ULD_431p");

    game.Process(curPlayer, HeroPowerTask(card2));
    EXPECT_EQ(curField.GetCount(), 6);
    EXPECT_EQ(curField[0]->GetAttack(), 1);
    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(curField[0]->HasReborn(), true);
    EXPECT_EQ(curField[1]->GetAttack(), 2);
    EXPECT_EQ(curField[1]->GetHealth(), 2);
    EXPECT_EQ(curField[1]->HasReborn(), true);
    EXPECT_EQ(curField[2]->GetAttack(), 1);
    EXPECT_EQ(curField[2]->GetHealth(), 1);
    EXPECT_EQ(curField[2]->HasReborn(), true);
}