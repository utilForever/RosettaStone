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

TEST(CoreCardsGen, CS1h_001)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask(curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 29);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask(curPlayer.GetHero()));

    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 30);
}

TEST(CoreCardsGen, CS2_017)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Northshire Cleric"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card1));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 0);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 3);

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 1);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 1);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), card1));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 1);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 0);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 0);
}

TEST(CoreCardsGen, CS2_034)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PRIEST;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Northshire Cleric"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card1));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 3);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask(card1));

    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
}

TEST(CoreCardsGen, CS2_049)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::SHAMAN;
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

    Task::Run(curPlayer, HeroPowerTask());
    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask());
    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask());
    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask());
    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask());
    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask());
    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask());
    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask());
    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curField.GetNumOfMinions(), 4u);
    EXPECT_EQ(opField.GetNumOfMinions(), 4u);
}

TEST(CoreCardsGen, CS2_056)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
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

    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 4);

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5);
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 28);
}

TEST(CoreCardsGen, CS2_083b)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
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

    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), true);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetAttack(), 1);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 2);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 1);
}

TEST(CoreCardsGen, CS2_101)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
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

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS2_102)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 0);

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 2);
}

TEST(CoreCardsGen, DS1h_292)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    Task::Run(curPlayer, HeroPowerTask());

    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);
}

TEST(CoreCardsGen, EX1_066)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Weapon(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), true);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);
}

TEST(CoreCardsGen, EX1_306)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Succubus"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 3u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(CoreCardsGen, CS2_041)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::ROGUE;
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
    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ancestral Healing"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, AttackTask(card3, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 2);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_088)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
    opPlayer.GetHero()->SetDamage(6);

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Guardian of Kings"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetBaseHealth(),
              opPlayer.GetHero()->GetHealth());
}

TEST(CoreCardsGen, CS1_112)
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
    curPlayer.GetHero()->SetDamage(4);

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Nova"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Argent Squire"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Worgen Infiltrator"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, AttackTask(card1, card4));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 28);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 5);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 7);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS1_113)
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

    const auto& curField = curPlayer.GetField();
    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mind Control"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Mind Control"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    auto curHero = curPlayer.GetHero();
    Task::Run(opPlayer, PlayCardTask::SpellTarget(curPlayer, card4, curHero));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 8u);
}

TEST(CoreCardsGen, EX1_129)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fan of Knives"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fan of Knives"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));

    EXPECT_EQ(opField.GetNumOfMinions(), 3u);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 7u);
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 7u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
}

TEST(CoreCardsGen, DS1_233)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mind Blast"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 25);
}

TEST(CoreCardsGen, CS2_029)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fireball"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fireball"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fireball"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fireball"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 24);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 24);
}

TEST(CoreCardsGen, CS2_025)
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

    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Explosion"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Explosion"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    EXPECT_EQ(opField.GetNumOfMinions(), 3u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
}

TEST(CoreCardsGen, CS2_037)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frost Shock"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frost Shock"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
}

TEST(CoreCardsGen, CS2_024)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostbolt"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostbolt"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostbolt"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostbolt"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    auto& curField = curPlayer.GetField();

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(opPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(curPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 1);
}

TEST(CoreCardsGen, CS2_026)
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frost Nova"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
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
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(opField.GetMinion(1)->GetHealth(), 1);
    EXPECT_EQ(opField.GetMinion(1)->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(opPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 0);
}

TEST(CoreCardsGen, CS2_032)
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flamestrike"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 3);
}

TEST(CoreCardsGen, CS2_023)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Intellect"));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(CoreCardsGen, EX1_277)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Missiles"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Missiles"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    int totalHealth = opPlayer.GetHero()->GetHealth();
    totalHealth += opPlayer.GetField().GetMinion(0)->GetHealth();
    EXPECT_EQ(totalHealth, 37);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    totalHealth = opPlayer.GetHero()->GetHealth();
    totalHealth += opPlayer.GetField().GetMinion(0)->GetHealth();
    EXPECT_EQ(totalHealth, 34);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    totalHealth = opPlayer.GetHero()->GetHealth();
    totalHealth += opPlayer.GetField().GetMinion(0)->GetHealth();
    EXPECT_EQ(totalHealth, 31);
}

TEST(CoreCardsGen, CS2_027)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mirror Image"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mirror Image"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mirror Image"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mirror Image"));

    auto& curField = curPlayer.GetField();
    EXPECT_EQ(curField.GetNumOfMinions(), 0u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 2);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 2);
    EXPECT_EQ(curField.GetMinion(1)->GetGameTag(GameTag::TAUNT), 1);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 4u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card3));
    EXPECT_EQ(curField.GetNumOfMinions(), 6u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card4));
    EXPECT_EQ(curField.GetNumOfMinions(), 7u);
}

TEST(CoreCardsGen, CS2_022)
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
        curPlayer, Cards::GetInstance().FindCardByName("Polymorph"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Polymorph"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 1);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS1_130)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Smite"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Smite"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Smite"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Smite"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetMinion(0)->GetHealth(), 5);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 28);
}

TEST(CoreCardsGen, CS2_093)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Consecration"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
}

TEST(CoreCardsGen, CS2_094)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Hammer of Wrath"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(CoreCardsGen, EX1_371)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Hand of Protection"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Hammer of Wrath"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);
}

TEST(CoreCardsGen, CS2_089)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Light"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Light"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    curPlayer.GetHero()->SetDamage(15);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    opField.GetMinion(0)->SetDamage(6);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 21);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
}

TEST(CoreCardsGen, DS1_185)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Shot"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Shot"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Shot"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Arcane Shot"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 28);
}

TEST(CoreCardsGen, CS2_007)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Healing Touch"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Healing Touch"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    curPlayer.GetHero()->SetDamage(15);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    opField.GetMinion(0)->SetDamage(6);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 23);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);
}

TEST(CoreCardsGen, CS2_062)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        curPlayer, Cards::GetInstance().FindCardByName("Hellfire"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 4);
}

TEST(CoreCardsGen, CS2_057)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shadow Bolt"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shadow Bolt"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 3);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
}

TEST(CoreCardsGen, CS2_122)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Raid Leader"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, AttackTask(card3, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);
}

TEST(CoreCardsGen, CS2_042)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fire Elemental"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fire Elemental"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer,
              PlayCardTask::MinionTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card2,
                                                    opField.GetMinion(0)));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 4);
}

TEST(CoreCardsGen, CS2_061)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
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

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Drain Life"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opPlayer.GetHero()->SetDamage(10);

    Task::Run(opPlayer, PlayCardTask::SpellTarget(opPlayer, card2, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 5);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 22);
}

TEST(CoreCardsGen, CS2_064)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Dread Infernal"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 29);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 6);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 29);
}

TEST(CoreCardsGen, CS2_075)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Sinister Strike"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);
}

TEST(CoreCardsGen, CS2_077)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Sprint"));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 8u);
}

TEST(CoreCardsGen, CS2_147)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Gnomish Inventor"));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
}

TEST(CoreCardsGen, CS2_084)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Hunter's Mark"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::SpellTarget(opPlayer, card2, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS2_039)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Windfury"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 0);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, AttackTask(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 24);
    EXPECT_EQ(curField.GetMinion(0)->GetExhausted(), true);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetExhausted(), false);

    Task::Run(curPlayer, AttackTask(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 18);
    EXPECT_EQ(curField.GetMinion(0)->GetExhausted(), true);
}

TEST(CoreCardsGen, CS2_076)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::HUNTER;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Assassinate"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS2_150)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::HUNTER;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Stormpike Commando"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Stormpike Commando"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer,
              PlayCardTask::MinionTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
}

TEST(CoreCardsGen, EX1_400)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::HUNTER;
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
        curPlayer, Cards::GetInstance().FindCardByName("Whirlwind"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    EXPECT_EQ(opField.GetMinion(1)->GetHealth(), 1);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 6);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 6);
}

TEST(CoreCardsGen, EX1_539)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Kill Command"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Kill Command"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ironfur Grizzly"));

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 22);
}

TEST(CoreCardsGen, CS2_008)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        curPlayer, Cards::GetInstance().FindCardByName("Moonfire"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Moonfire"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Moonfire"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Moonfire"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 29);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 29);
}

TEST(CoreCardsGen, CS2_072)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Backstab"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Backstab"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
}

TEST(CoreCardsGen, DS1_055)
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Darkscale Healer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Argent Squire"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card4));
    curField.GetMinion(0)->SetDamage(5);
    curField.GetMinion(2)->SetDamage(1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 2);
}

TEST(CoreCardsGen, CS2_114)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Cleave"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(1)->GetHealth(), 7);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);
    EXPECT_EQ(opField.GetMinion(1)->GetHealth(), 5);
}

TEST(CoreCardsGen, EX1_593)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Nightblade"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);
}

TEST(CoreCardsGen, EX1_587)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        curPlayer, Cards::GetInstance().FindCardByName("Windspeaker"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 0);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 0);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 0);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::WINDFURY), 1);
}

TEST(CoreCardsGen, EX1_308)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Soulfire"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 4u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Soulfire"));

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card3, opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 3u);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 26);
}

TEST(CoreCardsGen, EX1_278)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shiv"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shiv"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Kobold Geomancer"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card4));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 8u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curPlayer.currentSpellPower, 1);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 7u);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);
}

TEST(CoreCardsGen, CS2_087)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blessing of Might"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);
}

TEST(CoreCardsGen, CS2_141)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ironforge Rifleman"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS2_189)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Elven Archer"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, EX1_246)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        curPlayer, Cards::GetInstance().FindCardByName("Hex"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Hex"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 0);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_222)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        curPlayer, Cards::GetInstance().FindCardByName("Stormwind Champion"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 7);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 8);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 6);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 6);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    opField.GetMinion(0)->SetAttack(7);
    Task::Run(opPlayer, AttackTask(card3, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 7);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    opField.GetMinion(0)->SetAttack(6);
    Task::Run(opPlayer, AttackTask(card4, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, EX1_011)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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
    curPlayer.GetHero()->SetDamage(6);

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voodoo Doctor"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voodoo Doctor"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    opField.GetMinion(0)->SetDamage(1);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1,
                                                    curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 26);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card2, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
}

TEST(CoreCardsGen, DS1_183)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Multi-Shot"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    int totalHealth = opField.GetMinion(0)->GetHealth();
    EXPECT_EQ(totalHealth, 4);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(totalHealth, 4);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    totalHealth += opPlayer.GetField().GetMinion(1)->GetHealth();
    EXPECT_EQ(totalHealth, 8);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    totalHealth += opPlayer.GetField().GetMinion(2)->GetHealth();
    EXPECT_EQ(totalHealth, 12);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
    EXPECT_EQ(opField.GetNumOfMinions(), 3u);
    totalHealth = opField.GetMinion(0)->GetHealth();
    totalHealth += opPlayer.GetField().GetMinion(1)->GetHealth();
    totalHealth += opPlayer.GetField().GetMinion(2)->GetHealth();
    EXPECT_EQ(totalHealth, 6);
}

TEST(CoreCardsGen, EX1_173)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Starfire"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(CoreCardsGen, CS2_046)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Bloodlust"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 9);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 6);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);
}

TEST(CoreCardsGen, CS2_063)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Corruption"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS2_004)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Power Word: Shield"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 9);
}

TEST(CoreCardsGen, CS2_235)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
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
    curPlayer.GetHero()->SetDamage(6);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Northshire Cleric"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voodoo Doctor"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voodoo Doctor"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card2,
                                                    curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 26);

    curField.GetMinion(0)->SetDamage(2);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card3, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 3);
}

TEST(CoreCardsGen, EX1_622)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shadow Word: Death"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
}

TEST(CoreCardsGen, CS2_234)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shadow Word: Pain"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
}

TEST(CoreCardsGen, CS2_092)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Blessing of Kings"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 7);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 5);
}

TEST(CoreCardsGen, CS2_196)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Razorfen Hunter"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS2_012)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARRIOR;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Swipe"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Swipe"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 7);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetMinion(1)->GetHealth(), 1);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 29);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 3);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 25);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 2);
}

TEST(CoreCardsGen, EX1_606)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
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
    curPlayer.GetHero()->SetArmor(3);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shield Block"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 8);
}

TEST(CoreCardsGen, NEW1_003)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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
    curPlayer.GetHero()->SetDamage(8);

    auto& curField = curPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Sacrificial Pact"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voidwalker"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 22);
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 27);
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
}

TEST(CoreCardsGen, EX1_581)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::GetInstance().FindCardByName("Sap"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Blessing of Kings"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::SpellTarget(opPlayer, card3, card4));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 7);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 5);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card4));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 7u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 7u);
    EXPECT_EQ(opField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);
}

TEST(CoreCardsGen, NEW1_004)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
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
        curPlayer, Cards::GetInstance().FindCardByName("Vanish"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Voidwalker"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(curField.GetNumOfMinions(), 0u);
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 7u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, EX1_025)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Dragonling Mechanic"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
}

TEST(CoreCardsGen, CS2_013)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(9);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wild Growth"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wild Growth"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetRemainingMana(), 6);
    EXPECT_EQ(curPlayer.GetTotalMana(), 10);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetRemainingMana(), 3);
    EXPECT_EQ(curPlayer.GetTotalMana(), 10);
}

TEST(CoreCardsGen, EX1_169)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(9);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Innervate"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Innervate"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Dragonling Mechanic"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetRemainingMana(), 10);
    EXPECT_EQ(curPlayer.GetTemporaryMana(), 1);
    EXPECT_EQ(curPlayer.GetTotalMana(), 9);
    EXPECT_EQ(curPlayer.GetUsedMana(), 0);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetRemainingMana(), 6);
    EXPECT_EQ(curPlayer.GetTemporaryMana(), 0);
    EXPECT_EQ(curPlayer.GetTotalMana(), 9);
    EXPECT_EQ(curPlayer.GetUsedMana(), 3);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetRemainingMana(), 10);
    EXPECT_EQ(curPlayer.GetTemporaryMana(), 0);
    EXPECT_EQ(curPlayer.GetTotalMana(), 10);
    EXPECT_EQ(curPlayer.GetUsedMana(), 0);
}

TEST(CoreCardsGen, CS2_009)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mark of the Wild"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    auto& curField = curPlayer.GetField();

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 3);
}

TEST(CoreCardsGen, CS2_005)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Claw"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 2);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 2);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 28);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curPlayer.GetHero()->GetArmor(), 2);
}

TEST(CoreCardsGen, CS2_011)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Savage Roar"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 1);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 1);
}

TEST(CoreCardsGen, EX1_565)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flametongue Totem"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flametongue Totem"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flametongue Totem"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flametongue Totem"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card8 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 3);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card5));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 8);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 10);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 7);
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 3);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card6));
    EXPECT_EQ(curField.GetMinion(3)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(3)->GetHealth(), 4);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(3)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(3)->GetHealth(), 4);
    EXPECT_EQ(curField.GetMinion(4)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(4)->GetHealth(), 3);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card7));
    EXPECT_EQ(curField.GetMinion(5)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(5)->GetHealth(), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card4));
    EXPECT_EQ(curField.GetMinion(5)->GetAttack(), 7);
    EXPECT_EQ(curField.GetMinion(5)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(6)->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(6)->GetHealth(), 3);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card8));
    Task::Run(opPlayer, AttackTask(card8, card7));

    EXPECT_EQ(curField.GetMinion(4)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(4)->GetHealth(), 3);
    EXPECT_EQ(curField.GetMinion(5)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(5)->GetHealth(), 3);
}

TEST(CoreCardsGen, CS2_105)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Heroic Strike"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Heroic Strike"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 4);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 26);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Weapon(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 3);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 7);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 19);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 3);
}

TEST(CoreCardsGen, CS2_045)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Rockbiter Weapon"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Rockbiter Weapon"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card1, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 3);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 6);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
}

TEST(CoreCardsGen, CS2_003)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mind Vision"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    auto gainedCard = curPlayer.GetHand().GetCard(4);

    bool flag = false;
    for (auto& card : opPlayer.GetHand().GetAllCards())
    {
        if (card->id == gainedCard->id)
        {
            flag = true;
            break;
        }
    }

    EXPECT_TRUE(flag);
}

TEST(CoreCardsGen, CS2_074)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Deadly Poison"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(curPlayer, HeroPowerTask());
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetAttack(), 1);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 2);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetAttack(), 3);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 2);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetHero()->weapon->GetAttack(), 3);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 2);
}

TEST(CoreCardsGen, CS2_097)
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
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
    curPlayer.GetHero()->SetDamage(4);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Truesilver Champion"));

    Task::Run(curPlayer, PlayCardTask::Weapon(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 26);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetAttack(), 4);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 2);

    Task::Run(curPlayer, AttackTask(curPlayer.GetHero(), opPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->GetHealth(), 28);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 26);
    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 1);
}

TEST(CoreCardsGen, CS2_103)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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
        curPlayer, Cards::GetInstance().FindCardByName("Charge"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Dalaran Mage"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 0);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CANNOT_ATTACK_HEROES),
              0);

    Task::Run(curPlayer, AttackTask(card2, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CANNOT_ATTACK_HEROES),
              1);

    Task::Run(curPlayer, AttackTask(card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);

    Task::Run(curPlayer, AttackTask(card2, card3));
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CANNOT_ATTACK_HEROES),
              0);
}

TEST(CoreCardsGen, CS2_226)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostwolf Warlord"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostwolf Warlord"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frostwolf Warlord"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 5);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 6);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 6);
}

TEST(CoreCardsGen, CS2_236)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Divine Spirit"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 7);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, AttackTask(card3, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 8);
}

TEST(CoreCardsGen, CS2_237)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Starving Buzzard"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ironfur Grizzly"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
}

TEST(CoreCardsGen, DS1_070)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Houndmaster"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Starving Buzzard"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 0);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 4);
    EXPECT_EQ(curField.GetMinion(1)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, DS1_175)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Timber Wolf"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Timber Wolf"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Starving Buzzard"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card4));
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 2);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 5);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 2);
    EXPECT_EQ(curField.GetMinion(3)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(3)->GetHealth(), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    Task::Run(opPlayer, AttackTask(card5, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 2);
}

TEST(CoreCardsGen, DS1_178)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Tundra Rhino"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Timber Wolf"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Starving Buzzard"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 0);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetGameTag(GameTag::CHARGE), 1);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::CHARGE), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetGameTag(GameTag::CHARGE), 1);
    EXPECT_EQ(curField.GetMinion(2)->GetGameTag(GameTag::CHARGE), 1);
}

TEST(CoreCardsGen, DS1_184)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Tracking"));

    EXPECT_EQ(curPlayer.GetDeck().GetNumOfCards(), 5u);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_TRUE(curPlayer.choice.has_value());
    EXPECT_EQ(curPlayer.choice.value().choices.size(), 3u);

    Task::Run(curPlayer,
              ChooseTask::Pick(curPlayer, curPlayer.choice.value().choices[0]));
    EXPECT_EQ(curPlayer.GetDeck().GetNumOfCards(), 2u);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);
}

TEST(CoreCardsGen, EX1_019)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Shattered Sun Cleric"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ironfur Grizzly"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 3);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 3);

    Task::Run(curPlayer, PlayCardTask::MinionTarget(curPlayer, card1, card2));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), 4);
}

TEST(CoreCardsGen, EX1_084)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Murloc Raider"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Warsong Commander"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card3));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 3);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card4));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 2);
    EXPECT_EQ(curField.GetMinion(2)->GetAttack(), 4);
    EXPECT_EQ(curField.GetMinion(3)->GetAttack(), 2);
}

TEST(CoreCardsGen, EX1_244)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Totemic Might"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(curPlayer, HeroPowerTask());

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, HeroPowerTask());
    int totem1Health = curField.GetMinion(0)->GetHealth();
    int totem2Health = curField.GetMinion(1)->GetHealth();

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetHealth(), totem1Health + 2);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), totem2Health + 2);
    EXPECT_EQ(curField.GetMinion(2)->GetHealth(), 1);
}

TEST(CoreCardsGen, EX1_302)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mortal Coil"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mortal Coil"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetMinion(0)->GetHealth(), 1);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card3));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, EX1_399)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Gurubashi Berserker"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 2);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask(card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 5);

    Task::Run(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    Task::Run(opPlayer, HeroPowerTask(card1));
    EXPECT_EQ(curField.GetMinion(0)->GetAttack(), 8);
}

TEST(CoreCardsGen, EX1_506)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Murloc Tidehunter"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(curField.GetMinion(1)->GetAttack(), 1);
    EXPECT_EQ(curField.GetMinion(1)->GetHealth(), 1);
}