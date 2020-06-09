// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Views/BoardRefView.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace TestUtils;

TEST_CASE("[ReducedBoardView] - All")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    curPlayer->SetTotalMana(4);
    opPlayer->SetTotalMana(7);
    curPlayer->SetUsedMana(4);
    opPlayer->SetUsedMana(3);

    Card curWeaponCard = GenerateWeaponCard("weapon1", 3, 2);
    PlayWeaponCard(curPlayer, &curWeaponCard);

    Card opWeaponCard = GenerateWeaponCard("weapon2", 4, 1);
    PlayWeaponCard(opPlayer, &opWeaponCard);

    std::vector<Card> curCards, opCards;
    curCards.reserve(5);
    opCards.reserve(3);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        curCards.emplace_back(GenerateMinionCard(name + id, 1, 2));
        PlayMinionCard(curPlayer, &curCards[i]);
    }
    for (std::size_t i = 0; i < 3; ++i)
    {
        const auto id = static_cast<char>(i + 0x31);
        opCards.emplace_back(GenerateMinionCard(name + id, 3, 4));
        PlayMinionCard(opPlayer, &opCards[i]);
    }

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    ReducedBoardView reducedBoard1(board), reducedBoard2(board);

    CHECK(reducedBoard1 == reducedBoard2);
    CHECK_FALSE(reducedBoard1 != reducedBoard2);

    CHECK_EQ(reducedBoard1.GetTurn(), 1);
    CHECK_EQ(reducedBoard1.GetSide(), PlayerType::PLAYER1);

    CHECK_EQ(reducedBoard1.GetMyHero().attack, 3);
    CHECK_EQ(reducedBoard1.GetMyHeroPower().cardID, "HERO_01bp");
    CHECK_EQ(reducedBoard1.GetMyWeapon().durability, 2);
    CHECK_EQ(reducedBoard1.GetMyManaCrystal().total, 4);
    CHECK_EQ(reducedBoard1.GetMyManaCrystal().remaining, 0);
    CHECK_EQ(reducedBoard1.GetMyMinions().size(), 5);
    CHECK_EQ(reducedBoard1.GetMyMinions()[0].cardID, "test0");
    CHECK_EQ(reducedBoard1.GetMyMinions()[0].attack, 1);
    CHECK_EQ(reducedBoard1.GetMyMinions()[0].health, 2);
    CHECK_EQ(reducedBoard1.GetMyHand().size(), 4u);
    CHECK_EQ(reducedBoard1.GetMyDeck().count, 5);

    CHECK_EQ(reducedBoard1.GetOpHero().attack, 4);
    CHECK_EQ(reducedBoard1.GetOpHeroPower().cardID, "HERO_03bp");
    CHECK_EQ(reducedBoard1.GetOpWeapon().durability, 1);
    CHECK_EQ(reducedBoard1.GetOpManaCrystal().total, 7);
    CHECK_EQ(reducedBoard1.GetOpManaCrystal().remaining, 4);
    CHECK_EQ(reducedBoard1.GetOpMinions().size(), 3);
    CHECK_EQ(reducedBoard1.GetOpMinions()[0].cardID, "test1");
    CHECK_EQ(reducedBoard1.GetOpMinions()[0].attack, 3);
    CHECK_EQ(reducedBoard1.GetOpMinions()[0].health, 4);
    CHECK_EQ(reducedBoard1.GetOpHand().size(), 5u);
    CHECK_EQ(reducedBoard1.GetOpDeck().count, 5);
}