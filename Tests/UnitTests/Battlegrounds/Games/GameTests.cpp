// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Utils/GameUtils.hpp>

#include <vector>

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
        CHECK_EQ(player.remainCoin, 3);
        CHECK_EQ(player.totalCoin, 3);
        CHECK_EQ(player.currentTier, 1);
        CHECK_EQ(player.coinToUpgradeTavern, 5);

        const std::size_t numMinions =
            GetNumMinionsCanPurchase(player.currentTier);

        for (std::size_t i = 0; i < numMinions; ++i)
        {
            CHECK_EQ(player.tavernFieldZone[i].GetTier(), 1);
        }
    }

    Player& player1 = game.GetGameState().players.at(0);

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.handZone.GetCount(), 1);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.handZone.GetCount(), 0);
    CHECK_EQ(player1.recruitFieldZone.GetCount(), 1);

    player1.SellMinion(0);
    CHECK_EQ(player1.recruitFieldZone.GetCount(), 0);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 1);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8 + 1);

    player1.RefreshTavern();
    CHECK_EQ(player1.handZone.GetCount(), 0);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 3);
    CHECK_EQ(player1.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             game.GetGameState().minionPool.GetCount() - 3 * 8);

    player1.remainCoin = 10;

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.handZone.GetCount(), 1);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 2);
    CHECK_EQ(player1.remainCoin, 7);

    player1.PurchaseMinion(0);
    CHECK_EQ(player1.handZone.GetCount(), 2);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 1);
    CHECK_EQ(player1.remainCoin, 4);

    player1.PlayCard(0, 0);
    player1.PlayCard(0, 1);

    const int poolIdx1 = player1.recruitFieldZone[0].GetPoolIndex();
    const int poolIdx2 = player1.recruitFieldZone[1].GetPoolIndex();

    player1.RearrangeMinion(0, 1);
    CHECK_EQ(poolIdx1, player1.recruitFieldZone[1].GetPoolIndex());
    CHECK_EQ(poolIdx2, player1.recruitFieldZone[0].GetPoolIndex());

    player1.UpgradeTavern();
    CHECK_EQ(player1.currentTier, 1);
    CHECK_EQ(player1.remainCoin, 4);

    player1.remainCoin = 10;

    player1.UpgradeTavern();
    CHECK_EQ(player1.currentTier, 2);
    CHECK_EQ(player1.remainCoin, 5);

    player1.RefreshTavern();
    CHECK_EQ(player1.handZone.GetCount(), 0);
    CHECK_EQ(player1.tavernFieldZone.GetCount(), 4);
    CHECK_EQ(player1.remainCoin, 4);

    const std::size_t numMinions =
        GetNumMinionsCanPurchase(player1.currentTier);
    for (std::size_t i = 0; i < numMinions; ++i)
    {
        bool check = player1.tavernFieldZone[i].GetTier() == 1 ||
                     player1.tavernFieldZone[i].GetTier() == 2;
        CHECK_EQ(check, true);
    }

    for (auto& player : game.GetGameState().players)
    {
        player.CompleteRecruit();
    }

    CHECK_EQ(game.GetGameState().phase, Phase::COMBAT);
}