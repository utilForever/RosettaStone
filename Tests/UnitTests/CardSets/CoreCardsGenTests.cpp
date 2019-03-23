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

TEST(CoreCardsGen, EX1_066)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask::Weapon(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), true);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);
}

TEST(CoreCardsGen, EX1_306)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Succubus"));
    Generic::DrawCard(curPlayer,
                      Cards::GetInstance().FindCardByName("Stonetusk Boar"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    Generic::DrawCard(opPlayer,
                      Cards::GetInstance().FindCardByName("Fiery War Axe"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 0u);

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 2u);
}

TEST(CoreCardsGen, CS2_041)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

    auto& curField = curPlayer.GetField();
    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ancestral Healing"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));

    Task::Run(opPlayer, AttackTask(card3, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 1);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card2, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 2);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_088)
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;
    opPlayer.GetHero()->health = 24;

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Guardian of Kings"));

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->maxHealth, opPlayer.GetHero()->health);
}

TEST(CoreCardsGen, CS1_112)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;
    curPlayer.GetHero()->health = 26;

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
    curPlayer.currentMana = 10;
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card2));
    curPlayer.currentMana = 10;
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));

    Task::Run(curPlayer, EndTurnTask());
    Task::Run(opPlayer, EndTurnTask());

    Task::Run(curPlayer, AttackTask(card1, card4));
    EXPECT_EQ(curField.GetMinion(0)->health, 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card3));
    EXPECT_EQ(curPlayer.GetHero()->health, 28);
    EXPECT_EQ(opPlayer.GetHero()->health, 28);
    EXPECT_EQ(curField.GetMinion(0)->health, 5);
    EXPECT_EQ(curField.GetMinion(1)->health, 7);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS1_113)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

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
    curPlayer.currentMana = 10;
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    opPlayer.currentMana = 10;
    auto curHero = curPlayer.GetHero();
    Task::Run(opPlayer, PlayCardTask::SpellTarget(curPlayer, card4, curHero));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 2u);
}

TEST(CoreCardsGen, EX1_129)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

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

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));

    EXPECT_EQ(opField.GetNumOfMinions(), 3u);
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
    EXPECT_EQ(opPlayer.GetHero()->health, 30);
}

TEST(CoreCardsGen, DS1_233)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mind Blast"));

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opPlayer.GetHero()->health, 25);
}

TEST(CoreCardsGen, CS2_029)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

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

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));
    Task::Run(opPlayer, EndTurnTask());

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->health, 24);

    curPlayer.currentMana = 10;

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->health, 24);
}

TEST(CoreCardsGen, CS2_025)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

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

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card5));
    EXPECT_EQ(opField.GetNumOfMinions(), 3u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card1));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::Spell(curPlayer, card2));
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
    EXPECT_EQ(opPlayer.GetHero()->health, 30);
}

TEST(CoreCardsGen, CS2_037)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frost Shock"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Frost Shock"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card3));
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card4));
    EXPECT_EQ(opField.GetNumOfMinions(), 2u);

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card3));
    EXPECT_EQ(opField.GetMinion(0)->health, 1);
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

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;
    opPlayer.maximumMana = 10;
    opPlayer.currentMana = 10;

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

    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card6));
    Task::Run(opPlayer, EndTurnTask());

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card1, card6));
    EXPECT_EQ(opPlayer.GetField().GetNumOfMinions(), 0u);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card2, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->health, 27);
    EXPECT_EQ(opPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 1);

    curPlayer.currentMana = 10;

    Task::Run(curPlayer, PlayCardTask::SpellTarget(curPlayer, card3, card5));
    EXPECT_EQ(curField.GetMinion(0)->health, 4);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    Task::Run(curPlayer,
              PlayCardTask::SpellTarget(curPlayer, card4, curPlayer.GetHero()));
    EXPECT_EQ(curPlayer.GetHero()->health, 27);
    EXPECT_EQ(curPlayer.GetHero()->GetGameTag(GameTag::FROZEN), 1);
}