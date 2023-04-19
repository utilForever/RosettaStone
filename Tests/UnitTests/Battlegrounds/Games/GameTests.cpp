// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Utils/GameUtils.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

TEST_CASE("[Game] - Basic")
{
    Game game;
    game.Start();

    CHECK_EQ(game.GetGameState().phase, Phase::SELECT_HERO);

    auto minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount());

    for (auto& player : game.GetGameState().players)
    {
        for (const auto& hero : player.heroChoices)
        {
            auto heroCard = Cards::FindCardByDbfID(hero);
            CHECK_EQ(heroCard.GetCardType(), CardType::HERO);
            CHECK_EQ(heroCard.isCurHero, true);
        }

        player.SelectHero(1);
    }

    CHECK_EQ(game.GetGameState().phase, Phase::RECRUIT);

    for (auto& player : game.GetGameState().players)
    {
        CHECK_EQ(player.hero.health, player.hero.card.GetHealth());

        CHECK_EQ(player.remainCoin, 3);
        CHECK_EQ(player.totalCoin, 3);
        CHECK_EQ(player.currentTier, 1);
        CHECK_EQ(player.coinToUpgradeTavern, 5);

        const std::size_t numMinions =
            GetNumMinionsCanPurchase(player.currentTier);

        for (std::size_t i = 0; i < numMinions; ++i)
        {
            CHECK_EQ(player.tavern.fieldZone[i].GetTier(), 1);
        }
    }

    Player& player1 = game.GetGameState().players.at(0);

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8);

    player1.PlayCard(0, 0);
    bool checkCount = (player1.recruitField.GetCount() == 1 ||
                       player1.recruitField.GetCount() == 2);
    CHECK_EQ(player1.hand.GetCount(), 0);
    CHECK(checkCount);

    player1.SellMinion(0);
    checkCount = (player1.recruitField.GetCount() == 0 ||
                  player1.recruitField.GetCount() == 1);
    CHECK(checkCount);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 1);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8 + 1);

    player1.RefreshTavern();
    CHECK_EQ(player1.hand.GetCount(), 0);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 3);
    CHECK_EQ(player1.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8);

    player1.remainCoin = 7;

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 4);

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.hand.GetCount(), 2);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 1);
    CHECK_EQ(player1.remainCoin, 1);

    player1.PlayCard(0, 0);
    player1.PlayCard(0, 1);

    if (player1.recruitField.GetCount() >= 2)
    {
        const int poolIdx1 = player1.recruitField[0].GetPoolIndex();
        const int poolIdx2 = player1.recruitField[1].GetPoolIndex();

        player1.RearrangeMinion(0, 1);
        CHECK_EQ(poolIdx1, player1.recruitField[1].GetPoolIndex());
        CHECK_EQ(poolIdx2, player1.recruitField[0].GetPoolIndex());
    }

    player1.UpgradeTavern();
    CHECK_EQ(player1.currentTier, 1);
    CHECK_EQ(player1.remainCoin, 1);

    player1.remainCoin = 10;

    player1.UpgradeTavern();
    CHECK_EQ(player1.currentTier, 2);

    const bool check1 = player1.remainCoin == 5 || player1.remainCoin == 6 ||
                        player1.remainCoin == 7 || player1.remainCoin == 8;
    CHECK(check1);

    player1.RefreshTavern();

    const bool check2 =
        player1.hand.GetCount() == 0 || player1.hand.GetCount() == 1;
    CHECK(check2);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 4);

    const bool check3 = player1.remainCoin == 4 || player1.remainCoin == 5 ||
                        player1.remainCoin == 6 || player1.remainCoin == 7;
    CHECK(check3);

    const std::size_t numMinions =
        GetNumMinionsCanPurchase(player1.currentTier);
    for (std::size_t i = 0; i < numMinions; ++i)
    {
        bool check = player1.tavern.fieldZone[i].GetTier() == 1 ||
                     player1.tavern.fieldZone[i].GetTier() == 2;
        CHECK_EQ(check, true);
    }

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }
}

TEST_CASE("[Game] - CalculateRank")
{
    Game game;
    game.Start();

    auto& players = game.GetGameState().players;
    players.at(0).hero.health = 30;
    players.at(1).hero.health = 0;
    players.at(2).hero.health = 15;
    players.at(3).hero.health = 40;
    players.at(4).hero.health = 20;
    players.at(5).hero.health = 0;
    players.at(6).hero.health = 5;
    players.at(7).hero.health = 0;

    players.at(1).playState = PlayState::LOST;
    players.at(5).playState = PlayState::LOST;
    players.at(7).playState = PlayState::LOST;

    const auto result = game.CalculateRank();
    CHECK_EQ(result.size(), 5);
    CHECK_EQ(std::get<0>(result[0]), 3);
    CHECK_EQ(std::get<1>(result[0]), 40);
    CHECK_EQ(std::get<0>(result[1]), 0);
    CHECK_EQ(std::get<1>(result[1]), 30);
    CHECK_EQ(std::get<0>(result[2]), 4);
    CHECK_EQ(std::get<1>(result[2]), 20);
    CHECK_EQ(std::get<0>(result[3]), 2);
    CHECK_EQ(std::get<1>(result[3]), 15);
    CHECK_EQ(std::get<0>(result[4]), 6);
    CHECK_EQ(std::get<1>(result[4]), 5);
}

TEST_CASE("[Game] - DetermineOpponent")
{
    Game game;
    game.Start();

    auto& players = game.GetGameState().players;
    players.at(0).hero.health = 30;
    players.at(1).hero.health = 20;
    players.at(2).hero.health = 15;
    players.at(3).hero.health = 40;
    players.at(4).hero.health = 20;
    players.at(5).hero.health = 10;
    players.at(6).hero.health = 5;
    players.at(7).hero.health = 35;

    players.at(0).playerIdxFoughtLastTurn = 1;
    players.at(1).playerIdxFoughtLastTurn = 0;
    players.at(2).playerIdxFoughtLastTurn = 7;
    players.at(3).playerIdxFoughtLastTurn = 5;
    players.at(4).playerIdxFoughtLastTurn = 6;
    players.at(5).playerIdxFoughtLastTurn = 3;
    players.at(6).playerIdxFoughtLastTurn = 4;
    players.at(7).playerIdxFoughtLastTurn = 2;

    game.DetermineOpponent();
    for (auto& player : game.GetGameState().players)
    {
        CHECK_NE(game.FindPlayerNextFight(player.idx),
                 player.playerIdxFoughtLastTurn);
    }
}

TEST_CASE("[Game] - Freeze")
{
    Game game;
    game.Start();

    CHECK_EQ(game.GetGameState().phase, Phase::SELECT_HERO);

    for (auto& player : game.GetGameState().players)
    {
        player.SelectHero(1);
    }

    CHECK_EQ(game.GetGameState().phase, Phase::RECRUIT);

    Player& player1 = game.GetGameState().players.at(0);

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 0);

    player1.FreezeTavern();

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }

    CHECK_EQ(game.GetGameState().phase, Phase::RECRUIT);

    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 4);

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }

    CHECK_EQ(game.GetGameState().phase, Phase::RECRUIT);

    CHECK_EQ(player1.hand.GetCount(), 1);
    CHECK_EQ(player1.tavern.fieldZone.GetCount(), 3);
    CHECK_EQ(player1.remainCoin, 5);
}

TEST_CASE("[Game] - Ghost")
{
    Game game;
    game.Start();

    for (auto& player : game.GetGameState().players)
    {
        for (const auto& hero : player.heroChoices)
        {
            auto heroCard = Cards::FindCardByDbfID(hero);
            CHECK_EQ(heroCard.GetCardType(), CardType::HERO);
            CHECK_EQ(heroCard.isCurHero, true);
        }

        player.SelectHero(1);
    }

    auto& players = game.GetGameState().players;
    players.at(0).hero.health = 40;
    players.at(1).hero.health = 40;
    players.at(2).hero.health = 40;
    players.at(3).hero.health = 1;
    players.at(4).hero.health = 0;
    players.at(5).hero.health = 0;
    players.at(6).hero.health = 0;
    players.at(7).hero.health = 0;

    players.at(4).ProcessDefeat();
    players.at(5).ProcessDefeat();
    players.at(6).ProcessDefeat();
    players.at(7).ProcessDefeat();

    Minion minion1(Cards::FindCardByID("BGS_039"));
    Minion minion2(Cards::FindCardByID("BGS_039"));
    Minion minion3(Cards::FindCardByID("BGS_039"));

    players.at(0).hand.Add(minion1);
    players.at(1).hand.Add(minion2);
    players.at(2).hand.Add(minion3);
    players.at(0).PlayCard(0, 0);
    players.at(1).PlayCard(0, 0);
    players.at(2).PlayCard(0, 0);

    game.DetermineOpponent();

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }

    CHECK_EQ(game.GetGameState().ghostPlayerIdx, 3);
}

TEST_CASE("[Game] - Rank")
{
    Game game;
    game.Start();

    for (auto& player : game.GetGameState().players)
    {
        for (const auto& hero : player.heroChoices)
        {
            auto heroCard = Cards::FindCardByDbfID(hero);
            CHECK_EQ(heroCard.GetCardType(), CardType::HERO);
            CHECK_EQ(heroCard.isCurHero, true);
        }

        player.SelectHero(1);
    }

    auto minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8);

    auto& players = game.GetGameState().players;
    players.at(0).hero.health = 7;
    players.at(1).hero.health = 7;
    players.at(2).hero.health = 0;
    players.at(3).hero.health = 0;
    players.at(4).hero.health = 0;
    players.at(5).hero.health = 0;
    players.at(6).hero.health = 0;
    players.at(7).hero.health = 0;

    players.at(2).ProcessDefeat();
    players.at(3).ProcessDefeat();
    players.at(4).ProcessDefeat();
    players.at(5).ProcessDefeat();
    players.at(6).ProcessDefeat();
    players.at(7).ProcessDefeat();

    players.at(1).remainCoin = 10;

    players.at(1).PurchaseMinion(0);
    players.at(1).PlayCard(0, 0);
    players.at(1).PurchaseMinion(0);
    players.at(1).PlayCard(0, 0);
    players.at(1).PurchaseMinion(0);
    players.at(1).PlayCard(0, 0);

    game.DetermineOpponent();

    players.at(0).currentTier = 6;
    players.at(1).currentTier = 6;

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }

    CHECK_EQ(game.GetGameState().phase, Phase::COMPLETE);

    CHECK_EQ(players.at(0).rank, 2);
    CHECK_EQ(players.at(1).rank, 1);
    CHECK_EQ(players.at(2).rank, 8);
    CHECK_EQ(players.at(3).rank, 7);
    CHECK_EQ(players.at(4).rank, 6);
    CHECK_EQ(players.at(5).rank, 5);
    CHECK_EQ(players.at(6).rank, 4);
    CHECK_EQ(players.at(7).rank, 3);
}