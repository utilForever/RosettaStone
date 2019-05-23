// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

TEST(Expert1CardsGen, CS2_028)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blizzard"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(opPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 0);
}

TEST(Expert1CardsGen, EX1_012)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Bloodmage Thalnos"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blizzard"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.currentSpellPower, 1);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    Task::Run(opPlayer, AttackTask(card5, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 0u);
    EXPECT_EQ(curPlayer.currentSpellPower, 0);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(Expert1CardsGen, EX1_621)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Bloodmage Thalnos"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Circle of Healing"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card5 = Generic::DrawCard(
		opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, AttackTask(card5, card3));
    Task::Run(opPlayer, AttackTask(card4, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 6);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

	Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
}