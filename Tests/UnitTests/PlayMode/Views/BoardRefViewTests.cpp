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

TEST_CASE("[BoardRefView] - GetSide")
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

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetSide(), PlayerType::PLAYER1);
}

TEST_CASE("[BoardRefView] - GetTurn")
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

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetTurn(), 1);

    game.SetTurn(10);
    CHECK_EQ(board.GetTurn(), 10);
}

TEST_CASE("[BoardRefView] - GetCurrentPlayer")
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

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetCurrentPlayer(), curPlayer->playerType);
}

TEST_CASE("[BoardRefView] - GetFatigueDamage")
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

    curPlayer->GetHero()->fatigue = 3;
    opPlayer->GetHero()->fatigue = 5;

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetFatigueDamage(PlayerType::PLAYER1), 3);
    CHECK_EQ(board.GetFatigueDamage(PlayerType::PLAYER2), 5);
}

TEST_CASE("[BoardRefView] - GetTotalMana")
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

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetTotalMana(PlayerType::PLAYER1), 4);
    CHECK_EQ(board.GetTotalMana(PlayerType::PLAYER2), 7);
}

TEST_CASE("[BoardRefView] - GetUsedMana")
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

    curPlayer->SetUsedMana(4);
    opPlayer->SetUsedMana(3);

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetUsedMana(PlayerType::PLAYER1), 4);
    CHECK_EQ(board.GetUsedMana(PlayerType::PLAYER2), 3);
}

TEST_CASE("[BoardRefView] - GetTemporaryMana")
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

    curPlayer->SetTemporaryMana(2);
    opPlayer->SetTemporaryMana(5);

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetTemporaryMana(PlayerType::PLAYER1), 2);
    CHECK_EQ(board.GetTemporaryMana(PlayerType::PLAYER2), 5);
}

TEST_CASE("[BoardRefView] - GetOverloadOwed")
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

    curPlayer->SetOverloadOwed(6);
    opPlayer->SetOverloadOwed(3);

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetOverloadOwed(PlayerType::PLAYER1), 6);
    CHECK_EQ(board.GetOverloadOwed(PlayerType::PLAYER2), 3);
}

TEST_CASE("[BoardRefView] - GetOverloadLocked")
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

    curPlayer->SetOverloadLocked(7);
    opPlayer->SetOverloadLocked(2);

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetOverloadLocked(PlayerType::PLAYER1), 7);
    CHECK_EQ(board.GetOverloadLocked(PlayerType::PLAYER2), 2);
}

TEST_CASE("[BoardRefView] - GetRemainingMana")
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

    BoardRefView board(game, curPlayer->playerType);
    CHECK_EQ(board.GetRemainingMana(PlayerType::PLAYER1), 0);
    CHECK_EQ(board.GetRemainingMana(PlayerType::PLAYER2), 4);
}

TEST_CASE("[BoardRefView] - GetHero")
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

    BoardRefView board1(game, curPlayer->playerType);
    CHECK_EQ(board1.GetHero()->card->id, "HERO_01");

    BoardRefView board2(game, opPlayer->playerType);
    CHECK_EQ(board2.GetHero()->card->id, "HERO_03");
}

TEST_CASE("[BoardRefView] - GetOpponentHero")
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

    BoardRefView board1(game, curPlayer->playerType);
    CHECK_EQ(board1.GetHero()->card->id, "HERO_01");

    BoardRefView board2(game, opPlayer->playerType);
    CHECK_EQ(board2.GetHero()->card->id, "HERO_03");
}

TEST_CASE("[BoardRefView] - GetHeroPower")
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

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.GetHeroPower(PlayerType::PLAYER1).card->id, "HERO_01bp");
    CHECK_EQ(board.GetHeroPower(PlayerType::PLAYER2).card->id, "HERO_03bp");
}

TEST_CASE("[BoardRefView] - GetWeapon")
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

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.GetWeapon(PlayerType::PLAYER1), nullptr);
    CHECK_EQ(board.GetWeapon(PlayerType::PLAYER2), nullptr);
}

TEST_CASE("[BoardRefView] - GetHandCards")
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

    BoardRefView board1(game, curPlayer->playerType);
    CHECK_EQ(board1.GetHandCards().size(), 4u);

    BoardRefView board2(game, opPlayer->playerType);
    CHECK_EQ(board2.GetHandCards().size(), 5u);
}

TEST_CASE("[BoardRefView] - GetOpponentHandCards")
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

    BoardRefView board1(game, curPlayer->playerType);
    CHECK_EQ(board1.GetOpponentHandCards().at(0).second, false);

    BoardRefView board2(game, opPlayer->playerType);
    CHECK_EQ(board2.GetOpponentHandCards().at(0).second, false);
}

TEST_CASE("[BoardRefView] - GetOpponentHandCardCount")
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

    BoardRefView board1(game, curPlayer->playerType);
    CHECK_EQ(board1.GetOpponentHandCardCount(), 5);

    BoardRefView board2(game, opPlayer->playerType);
    CHECK_EQ(board2.GetOpponentHandCardCount(), 4);
}

TEST_CASE("[BoardRefView] - GetMinions")
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

    std::vector<Card> curCards, opCards;
    curCards.reserve(5);
    opCards.reserve(3);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        curCards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(curPlayer, &curCards[i]);
    }
    for (std::size_t i = 0; i < 3; ++i)
    {
        const auto id = static_cast<char>(i + 0x31);
        opCards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(opPlayer, &opCards[i]);
    }

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.GetMinions(PlayerType::PLAYER1).size(), 5u);
    CHECK_EQ(board.GetMinions(PlayerType::PLAYER1)[0]->card->id, "test0");
    CHECK_EQ(board.GetMinions(PlayerType::PLAYER2).size(), 3u);
    CHECK_EQ(board.GetMinions(PlayerType::PLAYER2)[0]->card->id, "test1");
}

TEST_CASE("[BoardRefView] - GetDeckCardCount")
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

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.GetDeckCardCount(PlayerType::PLAYER1), 5);
    CHECK_EQ(board.GetDeckCardCount(PlayerType::PLAYER2), 5);
}

TEST_CASE("[BoardRefView] - IsHeroAttackable")
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
    curPlayer->GetHero()->SetAttack(4);

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.IsHeroAttackable(PlayerType::PLAYER1), true);
    CHECK_EQ(board.IsHeroAttackable(PlayerType::PLAYER2), false);
}

TEST_CASE("[BoardRefView] - IsMinionAttackable")
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

    auto& curField = *(curPlayer->GetFieldZone());

    std::vector<Card> curCards, opCards;
    curCards.reserve(5);
    opCards.reserve(3);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        curCards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(curPlayer, &curCards[i]);
    }
    for (std::size_t i = 0; i < 3; ++i)
    {
        const auto id = static_cast<char>(i + 0x31);
        opCards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(opPlayer, &opCards[i]);
    }

    curField[0]->SetGameTag(GameTag::CHARGE, 1);
    curField[0]->SetExhausted(false);

    BoardRefView board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(board.IsMinionAttackable(PlayerType::PLAYER1, 0), true);
    CHECK_EQ(board.IsMinionAttackable(PlayerType::PLAYER1, 1), false);
    CHECK_EQ(board.IsMinionAttackable(PlayerType::PLAYER2, 0), false);
    CHECK_EQ(board.IsMinionAttackable(PlayerType::PLAYER2, 1), false);
}

TEST_CASE("[CurrentPlayerBoardRefView] - GetCurrentPlayer")
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

    auto curPlayerBoardRefView = CurrentPlayerBoardRefView(game);
    CHECK_EQ(curPlayerBoardRefView.GetCurrentPlayer()->playerType,
              PlayerType::PLAYER1);
}