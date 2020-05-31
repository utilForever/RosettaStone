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

    int numTier1Minion = 0, numTier2Minion = 0, numTier3Minion = 0,
        numTier4Minion = 0, numTier5Minion = 0, numTier6Minion = 0;

    for (auto& minionData : game.GetGameState().minionPool)
    {
        switch (std::get<0>(minionData).GetTier())
        {
            case 1:
                ++numTier1Minion;
                break;
            case 2:
                ++numTier2Minion;
                break;
            case 3:
                ++numTier3Minion;
                break;
            case 4:
                ++numTier4Minion;
                break;
            case 5:
                ++numTier5Minion;
                break;
            case 6:
                ++numTier6Minion;
                break;
            default:
                throw std::logic_error("Invalid minion in pool");
        }

        CHECK_EQ(std::get<1>(minionData), true);
    }

    CHECK_EQ(numTier1Minion,
             NUM_TIER1_MINIONS * NUM_COPIES_OF_EACH_TIER1_MINIONS);
    CHECK_EQ(numTier2Minion,
             NUM_TIER2_MINIONS * NUM_COPIES_OF_EACH_TIER2_MINIONS);
    CHECK_EQ(numTier3Minion,
             NUM_TIER3_MINIONS * NUM_COPIES_OF_EACH_TIER3_MINIONS);
    CHECK_EQ(numTier4Minion,
             NUM_TIER4_MINIONS * NUM_COPIES_OF_EACH_TIER4_MINIONS);
    CHECK_EQ(numTier5Minion,
             NUM_TIER5_MINIONS * NUM_COPIES_OF_EACH_TIER5_MINIONS);
    CHECK_EQ(numTier6Minion,
             NUM_TIER6_MINIONS * NUM_COPIES_OF_EACH_TIER6_MINIONS);

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
            CHECK_EQ(player.minionsInTavern.at(i).has_value(), true);
            CHECK_EQ(player.minionsInTavern.at(i).value().GetTier(), 1);
        }
    }

    Player& player = game.GetGameState().players.at(0);
    player.PurchaseMinion(0);
    CHECK_EQ(player.handZone.GetCount(), 1);
    CHECK_EQ(player.remainCoin, 0);
}