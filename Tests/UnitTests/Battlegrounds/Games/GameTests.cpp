// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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
    CHECK_EQ(static_cast<int>(minions.size()), NUM_TOTAL_TAVERN_MINIONS);

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

        const std::size_t numMinions =
            GetNumMinionsCanPurchase(player.currentTier);

        for (std::size_t i = 0; i < numMinions; ++i)
        {
            CHECK_EQ(player.tavernMinions[i].GetTier(), 1);
        }
    }

    Player& player = game.GetGameState().players.at(0);

    player.PurchaseMinion(0);
    CHECK_EQ(player.handZone.GetCount(), 1);
    CHECK_EQ(player.tavernMinions.GetCount(), 2);
    CHECK_EQ(player.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             NUM_TOTAL_TAVERN_MINIONS - 3 * 8);

    player.PlayCard(0, 0);
    CHECK_EQ(player.handZone.GetCount(), 0);
    CHECK_EQ(player.minions.GetCount(), 1);

    player.SellMinion(0);
    CHECK_EQ(player.minions.GetCount(), 0);
    CHECK_EQ(player.tavernMinions.GetCount(), 2);
    CHECK_EQ(player.remainCoin, 1);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             NUM_TOTAL_TAVERN_MINIONS - 3 * 8 + 1);

    player.RefreshTavern();
    CHECK_EQ(player.handZone.GetCount(), 0);
    CHECK_EQ(player.tavernMinions.GetCount(), 3);
    CHECK_EQ(player.remainCoin, 0);

    minions = game.GetGameState().minionPool.GetMinions(1, 6, true);
    CHECK_EQ(static_cast<int>(minions.size()),
             NUM_TOTAL_TAVERN_MINIONS - 3 * 8);
}